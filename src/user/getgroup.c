#include <errno.h>
#include <grp.h>
#include <string.h>
#include "user.h"

int cm_user_get_group(struct passwd *pw, char **group) {
	errno = 0;
	struct group *g = getgrgid(pw->pw_gid);
	if(g == NULL) {
		return CM_ERR_NOGRP;
	}
	strncpy(*group, g->gr_name, strlen(g->gr_name));
	return 0;
}
