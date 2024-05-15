#include "waitforchange.h"

#ifdef __linux__

#include <stdlib.h>
#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>

int init_waiter(struct waiter *waiter) {
    if (waiter == NULL) {
        return -1;
    }
    waiter->inotify_instance = inotify_init();
    if (waiter->inotify_instance == -1) {
        perror("inotify_init");
        return 1;
    }
    waiter->watched_files = NULL;
    waiter->watched_num = 0;
    waiter->watched_cap = 0;
    return 0;
}

struct waiter *new_waiter() {
    struct waiter *result = malloc(sizeof *result);
    if (!result) {
        return NULL;
    }
    if (init_waiter(result)) {
        perror("init_waiter");
        free(result);
        return NULL;
    }
    return result;
}

static int double_capacity(int **array, size_t *cap) {
    size_t new_cap = (*cap + 1) << 1;
    int *new_array = realloc(*array, sizeof **array * new_cap);
    if (new_array == NULL) {
        perror("realloc");
        return 1;
    }
    *cap = new_cap;
    *array = new_array;
    return 0;
}

static int add_to_waiter(struct waiter *waiter, int watch) {
    if (waiter->watched_num == waiter->watched_cap) {
        int err = double_capacity(&waiter->watched_files, &waiter->watched_cap);
        if (err) {
            perror("double_capacity");
            return 1;
        }
    }
    waiter->watched_files[waiter->watched_num++] = watch;
    return 0;
}

int waiter_add_watch(struct waiter *waiter, const char *pathname) {
    int watch = inotify_add_watch(waiter->inotify_instance, pathname, IN_MODIFY);
    if (watch == -1) {
        perror("inotify_add_watch");
        return 1;
    }
    if (add_to_waiter(waiter, watch)) {
        perror("add_to_waiter");
        return 1;
    }
    return 0;
}

int wait_for_event(struct waiter *waiter) {
    struct inotify_event event;
    ssize_t bytes = 0;
    while (bytes < sizeof event) {
        ssize_t new_bytes = 
            read(waiter->inotify_instance, (char*) &event + bytes, sizeof event - bytes);
        if (new_bytes == -1) {
            perror("read");
            break;
        }
        bytes += new_bytes;
    }
    return bytes < sizeof event;
}

int cleanup_waiter(struct waiter *waiter) {
    if (close(waiter->inotify_instance)) {
        perror("close inotify instance");
        return 1;
    }
    waiter->inotify_instance = -1;
    free(waiter->watched_files);
    waiter->watched_files = NULL;
    waiter->watched_num = 0;
    return 0;
}

#else
#error Platform not supported
#endif
