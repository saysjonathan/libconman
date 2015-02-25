#include <errno.h>
#include <grp.h>
#include <stdio.h>
#include <stdlib.h>
#include "group.h"

int cm_group_set_gid(char *group, int gid) {
	int i;
	static char buf[512], *membuf;
	struct group *g = getgrnam(group);
	membuf = malloc(512);

	errno = 0;
	if(g == NULL) {
		return -errno;
	}
	if((i = cm_join_members(g->gr_mem, membuf)) != 0) {
		return i;
	}
	snprintf(buf, sizeof(buf), "%s:%s:%d:%s\n", group, g->gr_passwd, gid, membuf);
	if((i = cm_replace_entry(group, "%[^:]:%*[^:]:%*d:%*[^:]", buf, GROUPFILE, TMPGROUPFILE)) != 0) {
		return i;
	}
	free(membuf);
	return 0;
}
