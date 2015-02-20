#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "link.h"

int cm_link_get_target(char *path, char **target) {
	char buf[256];
	ssize_t l;
	errno = 0;
	l = readlink(path, buf, sizeof(buf)-1);
	if(l == -1) {
		return -errno;
	}
	buf[l] = '\0';
	strncpy(*target, buf, sizeof(buf));
	return 0;
}
