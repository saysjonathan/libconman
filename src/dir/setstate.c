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

static int rmrecurse(char *path) {
	int i;
	char buf[1024];
	struct dirent *d;
	struct stat lst, st, ist;
	DIR *dp;

	errno = 0;
	if(lstat(path, &lst) < 0 || stat(path, &st) < 0) {
		return -errno;
	}
	if(!(S_ISDIR(lst.st_mode)) || (S_ISLNK(lst.st_mode) && S_ISDIR(st.st_mode))) {
		if(unlink(path) == -1) {
			return -errno;
		} else {
			return 0;
		}
	}
	if((dp = opendir(path)) == NULL) {
		return -errno;
	}
	while((d = readdir(dp)) != 0) {
		memset(buf, 0, sizeof(buf));
		if(strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0) {
			continue;
		}
		strncpy(buf, path, strlen(path));
		strncat(buf, "/", 1);
		strncat(buf, d->d_name, strlen(d->d_name));

		if(stat(buf, &ist) < 0) {
			return -errno;
		}
		if(S_ISDIR(ist.st_mode)) {
			if((i = rmrecurse(buf)) == -1) {
				return i;
			}
		}
		if(S_ISREG(ist.st_mode)) {
			if(unlink(buf) == -1) {
				return -errno;
			}
		}
	}
	closedir(dp);
	if(rmdir(path) == -1) {
		return -errno;
	}
	return 0;
}

static int rm(char *path, int recurse) {
	int i;
	errno = 0;
	if(recurse) {
		if((i = rmrecurse(path)) != 0) {
			return i;
		}
	} else {
		if(rmdir(path) == -1) {
			return -errno;
		}
	}
	return 0;
}

int cm_dir_set_state(char *path, int state, int recurse) {
	if(state == CM_PRESENT) {
		return create(path);
	} else if(state == CM_ABSENT) {
		return rm(path, recurse);
	}
	return -1;
}
