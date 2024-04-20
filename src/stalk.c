#include <stdio.h>
#include <sys/stat.h>

void stalk(const char *filename) {
    struct stat statbuf;
    time_t last_time = 0;

    while (1) {
        int stat_error = stat(filename, &statbuf);
       
        if (stat_error) {
            fprintf(stderr, "Error checking file %s:", filename);
            perror("");
        }
        
        time_t new_time = statbuf.st_mtim.tv_sec;
        if (new_time == last_time) {
            continue;
        }
        last_time = new_time;
        printf("File last changed at %ld\n", last_time);
    }
}
