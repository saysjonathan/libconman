#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "common.h"

int cm_append_entry(char *line, size_t size, char *file) {
	int fd;
	errno = 0;
	if((fd = open(file, O_RDWR|O_APPEND)) == -1) {
		return -errno;
	}
	if(write(fd, line, size) == -1) {
		close(fd);
		return -errno;
	}
	close(fd);
	return 0;
}
