#include <errno.h>
#include <string.h>
#include "group.h"

int cm_group_get_passwd(struct group *gr, char **passwd) {
	size_t bs = sizeof(MAX_GROUP_LEN);
	errno = 0;
	strncpy(*passwd, gr->gr_passwd, bs);
	return 0;
}
