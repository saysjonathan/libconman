#include <errno.h>
#include <unistd.h>
#include "link.h"

static int create(char *path, char *target) {
	errno = 0;
	if(symlink(target, path) == -1) {
		return -errno;
	}
	return 0;
}

static int remove(char *path) {
	errno = 0;
	if((unlink(path)) == -1) {
		return -errno;
	}
	return 0;
}

int cm_link_set_state(char *path, int state, char *target) {
	if(state == CM_PRESENT) {
		return create(path, target);
	} else if(state == CM_ABSENT) {
		return remove(path);
	}
	return -1;
}
