#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "file.h"

static int _copy(char *path, char *source) {
	char buf[2048];
	size_t bs = sizeof(buf);
	int i = 0;
	FILE *s, *t;

	errno = 0;
	if((s = fopen(source, "r")) == NULL) {
		return -errno;
	}
	if((t = fopen(path, "w+")) == NULL) {
		fclose(s);
		return -errno;
	}
	while(fgets(buf, bs, s) != NULL) {
		if(fprintf(t, buf) == -1) {
			i = -errno;
			goto cleanup;
		}
	}
	goto cleanup;
cleanup:
	fclose(s);
	fclose(t);
	return i;
}

static int _create(char *path) {
	int fd;
	errno = 0;
	if((fd = open(path, O_CREAT|O_EXCL,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)) == -1) {
		return -errno;
	}
	close(fd);
	return 0;
}

static int _remove(char *path) {
	errno = 0;
	if((unlink(path)) == -1) {
		return -errno;
	}
	return 0;
}

int cm_file_set_state(char *path, char *source, int state) {
	if(state == CM_PRESENT) {
		if(strlen(source) != 0) {
			return _copy(path, source);
		} else {
			return _create(path);
		}
	} else if(state == CM_ABSENT) {
		return _remove(path);
	}
	return -1;
}
