#ifndef _WAITFORCHANGE_H
#define _WAITFORCHANGE_H

struct waiter;

#ifdef __linux__

struct waiter {
    int inotify_instance;
    int *watched_files;
    int watched_num;
};

#endif // linux waiter type

int init_waiter(struct waiter *waiter);

struct waiter *new_waiter();

int waitforchange(struct waiter *waiter, const char *pathname);

int cleanup_waiter(struct waiter *waiter);

#endif
