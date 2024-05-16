#ifndef _WAITFORCHANGE_H
#define _WAITFORCHANGE_H

#include <stdlib.h>

struct waiter;

#ifdef __linux__

struct watch {
    int file;
    const char *path;
};

struct waiter {
    int inotify_instance;
    struct watch *watches;
    size_t num;
    size_t cap;
};

#endif // linux waiter type

int init_waiter(struct waiter *waiter);

struct waiter *new_waiter();

int waiter_add_watch(struct waiter *waiter, const char *pathname);

int waiter_remove_watch(struct waiter *waiter, const char *pathname);

int wait_for_event(struct waiter *waiter);

int cleanup_waiter(struct waiter *waiter);

#endif
