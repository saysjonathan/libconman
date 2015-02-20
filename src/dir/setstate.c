#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "dir.h"

static int create(char *path) {
	errno = 0;
	if(mkdir(path, S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH) == -1) {
		return -errno;
	}
	return 0;
}

static int remove(char *path) {
	errno = 0;
	if(rmdir(path) == -1) {
		return -errno;
	}
	return 0;
}

int cm_dir_set_state(char *path, int state) {
	if(state == CM_PRESENT) {
		return create(path);
	} else if(state == CM_ABSENT) {
		return remove(path);
	}
	return -1;
}
