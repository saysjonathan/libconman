#include <errno.h>
#include <grp.h>
#include <string.h>
#include "common.h"

int cm_get_group(struct stat *s, char **group) {
	size_t bs = sizeof(*group);
	errno = 0;
	struct group *gr = getgrgid(s->st_gid);
	if(gr == NULL) {
		return -errno;
	}
	strncpy(*group, gr->gr_name, bs);
	return 0;
}
