#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"

int cm_file_set_mode(char *path, char *mode) {
	char *e;
	mode_t m = strtol(mode, &e, 8);
	errno = 0;
	if(chmod(path, m) != 0) {
		return -errno;
	}
	return 0;
}
