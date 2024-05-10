#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int startmessage(const char *fname) {
    static const int BUFSIZE = 200;
    char wdirbuf[BUFSIZE];
    char pathbuf[BUFSIZE];
    char normpathbuf[BUFSIZE];
    snprintf(pathbuf, BUFSIZE, "%s/%s", getcwd(wdirbuf, BUFSIZE), fname);
    char *resolved_path = realpath(pathbuf, normpathbuf);
    if (resolved_path == NULL) {
        perror("Error checking file");
        return -1;
    }
    return printf("Stalking %s\n", resolved_path);
}
