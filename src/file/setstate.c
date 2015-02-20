#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "file.h"

static int create(char *path) {
	int fd;
	errno = 0;
	if((fd = open(path, O_CREAT|O_EXCL,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)) == -1) {
		return -errno;
	}
	close(fd);
	return 0;
}

static int remove(char *path) {
	errno = 0;
	if((unlink(path)) == -1) {
		return -errno;
	}
	return 0;
}

int cm_file_set_state(char *path, int state) {
	if(state == CM_PRESENT) {
		return create(path);
	} else if(state == CM_ABSENT) {
		return remove(path);
	}
	return -1;
}
