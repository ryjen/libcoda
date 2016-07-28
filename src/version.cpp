#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <stdio.h>

char* librj_version()
{
    static char buf[BUFSIZ + 1] = {0};
    snprintf(buf, BUFSIZ, "%s", PACKAGE_VERSION);
    return buf;
}
