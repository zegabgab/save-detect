#include <stdio.h>
#include "stalk.h"

const int FAILURE = 69;

void usage(void) {
    fprintf(stderr, "Usage: save-detect filename\n");
}

int main(int argc, char **argv) {
    if (argc != 2) {
        usage();
        return FAILURE;
    }
    stalk(argv[1]);
}

