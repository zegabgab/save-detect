#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include "wait/waitforchange.h"

static int print_time(FILE *stream, time_t *time);

int stalk(const char *filename) {
    struct waiter waiter;
    if (init_waiter(&waiter)) {
        perror("init_waiter");
        return 1;
    }
    if (waiter_add_watch(&waiter, filename)) {
        perror("waiter_add_watch");
    }
    if (wait_for_event(&waiter)) {
        perror("wait_for_event");
        return 1;
    }
    time_t now;
    time(&now);
    printf("[");
    print_time(stdout, &now);
    printf("] File changed!\n");
    if (cleanup_waiter(&waiter)) {
        perror("cleanup_waiter");
        return 1;
    }
    return 0;
}

static int print_time(FILE *stream, time_t *timep) {
    static struct tm time_breakdown;
    static struct tm *time_result = NULL;
    time_result = localtime_r(timep, &time_breakdown);

    if (time_result == NULL) {
        return -1;
    }
    return fprintf(
            stream,
            "%02d:%02d:%02d",
            time_breakdown.tm_hour,
            time_breakdown.tm_min,
            time_breakdown.tm_sec);
}

