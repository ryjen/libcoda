
#include <stdio.h>

char *libcoda_version() {
  static char buf[BUFSIZ + 1] = {0};
  snprintf(buf, BUFSIZ, "%s", LIBRARY_VERSION);
  return buf;
}
