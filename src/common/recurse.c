#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "common.h"

int cm_recurse(char *path, char *arg, int (*fn)(char *, char *, int)) {
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
		return fn(path, arg, 0);
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
			if((i = fn(buf, arg, 1)) != 0) {
				return i;
			}
		}
		if(S_ISREG(ist.st_mode)) {
			if((i = fn(buf, arg, 0)) != 0) {
				return i;
			}
		}
	}
	closedir(dp);
	return 0;
}
