#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "file.h"

int cm_file_get_mode(struct stat *s, char **mode) {
	char buf[8];
	size_t bs = sizeof(buf);
	errno = 0;
	if(snprintf(buf, bs, "%lo", (unsigned long)s->st_mode) < 0) {
		return -errno;
	}
	strcpy(*mode,(buf+strlen(buf)-4));
	return 0;
}
