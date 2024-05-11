#include <stdio.h>
#include <sys/inotify.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

static int print_time(FILE *stream, time_t *time);

int stalk(const char *filename) {
    int notify = inotify_init();
    if (notify == -1) {
        return 1;
    }
    int watch = inotify_add_watch(notify, filename, IN_MODIFY);
    struct inotify_event mod_event;

    ssize_t bytes = 0;
    while (bytes < sizeof mod_event) {
        ssize_t new_bytes = read(notify, (char*) &mod_event + bytes, sizeof mod_event - bytes);
        if (new_bytes == -1) {
            inotify_rm_watch(notify, watch);
            if (close(notify) != 0) {
                perror("close inotify instance");
            }
            return 1;
        }
        bytes += new_bytes;
    }

    time_t now;
    time(&now);
    printf("[");
    print_time(stdout, &now);
    printf("] File changed!\n");
    inotify_rm_watch(notify, watch);
    if (close(notify) != 0) {
        perror("close inotify instance");
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

