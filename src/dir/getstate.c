#include <errno.h>
#include "dir.h"

int cm_dir_get_state(char *path, struct stat *s) {
	int i;
	errno = 0;
	i = stat(path, s);
	if(i == -1) {
		if(errno == ENOENT) {
			return CM_ABSENT;
		} else {
			return -errno;
		}
	} else {
		if(S_ISDIR(s->st_mode)) {
			return CM_PRESENT;
		} else {
			return CM_ERR_NOTDIR;
		}
	}
}
