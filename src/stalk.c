#include <stdio.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

static void print_error(const char *filename);
static int print_time(FILE *stream, time_t *time);

int stalk(const char *filename) {
    struct stat statbuf;
    int filedesc = open(filename, O_RDONLY);
    if (filedesc < 0) {
        return 1;
    }
    if (flock(filedesc, LOCK_SH)) {
        close(filedesc);
        return 2;
    }

    int stat_error = fstat(filedesc, &statbuf);

    if (stat_error) {
        print_error(filename);
        return 1;
    }

    long last_time = statbuf.st_mtim.tv_nsec;

    while (1) {
        stat_error = fstat(filedesc, &statbuf);

        if (stat_error) {
            print_error(filename);
        }
        
        long new_time = statbuf.st_mtim.tv_nsec;
        if (new_time == last_time) {
            continue;
        }
        last_time = new_time;
        printf("[");
        print_time(stdout, &statbuf.st_mtim.tv_sec);
        printf("] File changed!\n");
    }
}

static void print_error(const char *filename) {
    fprintf(stderr, "Error checking file %s: ", filename);
    perror("");
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

