#include <unistd.h>
#include "checkfile.h"

bool confirmaccessible(const char *pathname) {
    return access(pathname, F_OK);
}

