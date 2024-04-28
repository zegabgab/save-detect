#include <stdio.h>
#include "stalk.h"
#include "startmessage.h"

const int FAILURE = 69;

int usage(void) {
    return fprintf(stderr, "Usage: save-detect filename\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        usage();
        return FAILURE;
    }

    const char *const file = argv[1];
    startmessage(file);
    stalk(file);
}

