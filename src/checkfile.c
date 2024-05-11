#include "checkfile.h"

#ifdef __unix__
#include <unistd.h>

bool confirmaccessible(const char *pathname) {
    return access(pathname, F_OK);
}

#else
#error Platform not supported
#endif
