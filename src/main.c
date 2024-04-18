#include <stdio.h>

void usage(void) {
    fprintf(stderr, "Usage: save-detect filename\n");
}

void stalk(char *filename) {
    printf("Stalking %s\n", filename);
}

int main(int argc, char **argv) {
    if (argc < 2 || argc > 2) {
        usage();
        return 69;
    }
    stalk(argv[1]);
}
