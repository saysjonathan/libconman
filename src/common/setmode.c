#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "common.h"

int cm_set_mode(char *path, char *mode) {
	char *e;
	mode_t m = strtol(mode, &e, 8);
	errno = 0;
	if(chmod(path, m) != 0) {
		return -errno;
	}
	return 0;
}
