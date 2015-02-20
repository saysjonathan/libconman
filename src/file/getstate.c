#include <errno.h>
#include "file.h"

int cm_file_get_state(char *path, struct stat *s) {
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
		if(S_ISREG(s->st_mode)) {
			return CM_PRESENT;
		} else {
			return CM_ERR_NOTFILE;
		}
	}
}
