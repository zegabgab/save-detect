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

int waitforchange(struct waiter *waiter, const char *pathname) {
    return -1;
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
