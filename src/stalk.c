#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>

static void print_error(const char *filename);
static void print_time(FILE *stream, time_t *time);

void stalk(const char *filename) {
    struct stat statbuf;

    int stat_error = stat(filename, &statbuf);
    time_t last_time = statbuf.st_mtim.tv_sec;

    if (stat_error && errno == ENOENT) {
        print_error(filename);
        return;
    }
    if (!stat_error) {
        printf("Currently stalking %s\n", filename);
    }

    while (1) {
        stat_error = stat(filename, &statbuf);

        if (stat_error && errno != ENOENT) {
            print_error(filename);
        }
        
        time_t new_time = statbuf.st_mtim.tv_sec;
        if (new_time == last_time) {
            continue;
        }
        last_time = new_time;
        printf("File changed!\nTime: %ld\nFormatted time: ", last_time);
        print_time(stdout, &statbuf.st_mtim.tv_sec);
    }
}

static void print_error(const char *filename) {
    fprintf(stderr, "Error checking file %s: ", filename);
    perror("");
}

static void print_time(FILE *stream, time_t *time) {
    static const int BUFSIZE = 100;
    char buf[BUFSIZE];
    ctime_r(time, buf);
    fprintf(stream, "%s", buf);
}

