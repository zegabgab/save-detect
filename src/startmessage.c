#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int startmessage(const char *fname) {
    static const int BUFSIZE = 200;
    char wdirbuf[BUFSIZE];
    char pathbuf[BUFSIZE];
    char normpathbuf[BUFSIZE];
    snprintf(pathbuf, BUFSIZE, "%s/%s", getcwd(wdirbuf, BUFSIZE), fname);
    return printf("Stalking %s\n", realpath(pathbuf, normpathbuf));
}
