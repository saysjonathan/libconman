#include <errno.h>
#include <unistd.h>
#include "link.h"

int cm_link_get_state(char *path, struct stat *s) {
	int i;
	errno = 0;
	i = lstat(path, s);
	if(i == -1) {
		if(errno == ENOENT) {
			return CM_ABSENT;
		} else {
			return -errno;
		}
	} else {
		if(S_ISLNK(s->st_mode)) {
			return CM_PRESENT;
		} else {
			return CM_ERR_NOTLINK;
		}
	}
}
