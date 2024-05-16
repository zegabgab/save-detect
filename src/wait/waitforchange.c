#include "waitforchange.h"

#ifdef __linux__

#include <stdlib.h>
#include <stdio.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>

int init_waiter(struct waiter *waiter) {
    if (waiter == NULL) {
        return -1;
    }
    waiter->inotify_instance = inotify_init();
    if (waiter->inotify_instance == -1) {
        perror("inotify_init");
        return 1;
    }
    waiter->watches = NULL;
    waiter->num = 0;
    waiter->cap = 0;
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

static int double_capacity(struct waiter *waiter) {
    size_t new_cap = (waiter->cap + 1) << 1;
    struct watch *new_array = realloc(waiter->watches, sizeof *waiter->watches * new_cap);
    if (new_array == NULL) {
        perror("realloc");
        return 1;
    }
    waiter->cap = new_cap;
    waiter->watches = new_array;
    return 0;
}

static int add_to_waiter(struct waiter *waiter, struct watch watch) {
    if (waiter->num == waiter->cap) {
        int err = double_capacity(waiter);
        if (err) {
            perror("double_capacity");
            return 1;
        }
    }
    waiter->watches[waiter->num++] = watch;
    return 0;
}

int waiter_add_watch(struct waiter *waiter, const char *pathname) {
    struct watch watch;
    watch.file = inotify_add_watch(waiter->inotify_instance, pathname, IN_MODIFY);
    if (watch.file == -1) {
        perror("inotify_add_watch");
        return 1;
    }
    watch.path = pathname;
    if (add_to_waiter(waiter, watch)) {
        perror("add_to_waiter");
        return 1;
    }
    return 0;
}

int wait_for_event(struct waiter *waiter) {
    char buffer[sizeof(struct inotify_event) + NAME_MAX + 1];
    ssize_t bytes = 0;
    while (bytes < sizeof(struct inotify_event)) {
        ssize_t new_bytes = 
            read(waiter->inotify_instance, buffer + bytes, sizeof(struct inotify_event) - bytes);
        if (new_bytes == -1 && errno != EINTR) {
            perror("read");
            break;
        }
        bytes += new_bytes >= 0 ? new_bytes : 0;
    }
    size_t len = ((struct inotify_event*) buffer)->len + sizeof(struct inotify_event);
    while (bytes < len) {
        ssize_t new_bytes = 
            read(waiter->inotify_instance, buffer + bytes, len - bytes);
        if (new_bytes == -1 && errno != EINTR) {
            perror("read");
            break;
        }
        bytes += new_bytes >= 0 ? new_bytes : 0;
    }
    return bytes < sizeof(struct inotify_event);
}

int cleanup_waiter(struct waiter *waiter) {
    if (close(waiter->inotify_instance)) {
        perror("close inotify instance");
        return 1;
    }
    waiter->inotify_instance = -1;
    free(waiter->watches);
    waiter->watches = NULL;
    waiter->num = 0;
    waiter->cap = 0;
    return 0;
}

#else
#error Platform not supported
#endif
