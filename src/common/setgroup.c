#include <errno.h>
#include <grp.h>
#include <unistd.h>
#include "common.h"

int cm_set_group(char *path, char *group) {
	struct group *g = getgrnam(group);
	if(g == NULL) {
		return CM_ERR_NOGRP;
	}
	errno = 0;
	if(chown(path, -1, g->gr_gid) != 0) {
		return -errno;
	}
	return 0;
}
