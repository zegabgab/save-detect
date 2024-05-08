#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "stalk.h"
#include "startmessage.h"

const int FAILURE = 69;

static bool parse_args(int argc, char **argv, char **file, bool *fun);

static void funstartmessage() {
    printf("oh boy, here we go again\n");
}

int usage(void) {
    return fprintf(stderr, "Usage: save-detect filename\n");
}

int main(int argc, char **argv) {
    char *file;
    bool fun;

    if (parse_args(argc, argv, &file, &fun)) {
        usage();
        return FAILURE;
    }
    if (fun) {
        funstartmessage();
    } else {
        startmessage(file);
    }
    stalk(file);
}

static bool parse_args(int argc, char **argv, char **file, bool *fun) {
    if (argc < 2) {
        return true;
    }
    *fun = false;
    bool file_found = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--fun") == 0) {
            *fun = true;
        } else {
            *file = file_found ? *file : argv[i];
            file_found = true;
        }
    }
    return !file_found;
}

