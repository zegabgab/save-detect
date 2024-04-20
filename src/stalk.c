#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

static void print_error(const char *filename);

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
        printf("File last changed at %ld\n", last_time);
    }
}

static void print_error(const char *filename) {
    fprintf(stderr, "Error checking file %s: ", filename);
    perror("");
}

