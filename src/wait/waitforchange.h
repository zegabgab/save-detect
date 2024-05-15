#ifndef _WAITFORCHANGE_H
#define _WAITFORCHANGE_H

#include <stdlib.h>

struct waiter;

#ifdef __linux__

struct waiter {
    int inotify_instance;
    int *watched_files;
    size_t watched_num;
    size_t watched_cap;
};

#endif // linux waiter type

int init_waiter(struct waiter *waiter);

struct waiter *new_waiter();

int waiter_add_watch(struct waiter *waiter, const char *pathname);

int wait_for_event(struct waiter *waiter);

int cleanup_waiter(struct waiter *waiter);

#endif
