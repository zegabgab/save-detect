#include "waitforchange.h"

#ifdef __linux__

#include <sys/inotify.h>
#include "waitforchange.h"

int init_waiter() {
    return -1;
}

int waitforchange(const char *pathname) {
    return -1;
}

int cleanup_waiter() {
    return -1;
}

#else
#error Platform not supported
#endif
