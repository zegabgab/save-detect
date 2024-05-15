#include "waitforchange.h"

#ifdef __linux__

#include <stdlib.h>
#include <sys/inotify.h>

int init_waiter(struct waiter *waiter) {
    if (waiter == NULL) {
        return -1;
    }
    waiter->inotify_instance = -1;
    waiter->watched_files = NULL;
    waiter->watched_num = 0;
    return 0;
}

struct waiter *new_waiter() {
    struct waiter *result = malloc(sizeof *result);
    if (!result) {
        return NULL;
    }
    return result;
}

int waitforchange(struct waiter *waiter, const char *pathname) {
    return -1;
}

int cleanup_waiter(struct waiter *waiter) {
    return -1;
}

#else
#error Platform not supported
#endif
