#include <errno.h>
#include <stdio.h>
#include "common.h"

int cm_rm(char *path, char *unused, int recurse) {
	errno = 0;
	if(recurse) {
		cm_recurse(path, NULL, cm_rm);
	}
	if(remove(path) == -1) {
		return -errno;
	}
	return 0;
}
