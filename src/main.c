#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "checkfile.h"
#include "stalk.h"
#include "startmessage.h"

struct args {
    char *file;
    bool fun;
};

const int FAILURE = 69;

static struct args *parse_args(int argc, char **argv, struct args *args);

static void funstartmessage() {
    printf("oh boy, here we go again\n");
}

int usage(void) {
    return fprintf(stderr, "Usage: save-detect filename\n");
}

int main(int argc, char **argv) {
    struct args args;

    if (parse_args(argc, argv, &args) == NULL) {
        usage();
        return FAILURE;
    }
    if (confirmaccessible(args.file)) {
        perror(args.file);
        return FAILURE;
    }
    if (args.fun) {
        funstartmessage();
    } else {
        startmessage(args.file);
    }
    if (stalk(args.file)) {
        perror("stalk");
        return FAILURE;
    }
}

static struct args *parse_args(int argc, char **argv, struct args *args) {
    if (argc < 2) {
        return NULL;
    }
    args->fun = false;
    bool file_found = false;
    for (int i = 1; i < argc; i++) {
        bool this_fun = strcmp(argv[i], "--fun") == 0;
        args->fun |= this_fun;
        args->file = (!file_found && !this_fun) ? argv[i] : args->file;
        file_found |= !this_fun;
    }
    return file_found ? args : NULL;
}

