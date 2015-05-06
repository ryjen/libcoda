#include "config.h"
#include <stdio.h>

char* arg3_version()
{
	static char buf[BUFSIZ + 1] = {0};
	snprintf(buf, BUFSIZ, "%s", VERSION);
	return buf;
}