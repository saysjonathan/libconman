#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "dir.h"

static int create(char *path) {
	errno = 0;
	if(mkdir(path, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH) == -1) {
		return -errno;
	}
	return 0;
}

int cm_dir_set_state(char *path, int state, int recurse) {
	if(state == CM_PRESENT) {
		return create(path);
	} else if(state == CM_ABSENT) {
		return cm_rm(path, NULL, recurse);
	}
	return -1;
}
