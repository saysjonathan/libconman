#include <stdlib.h>
#include "group.h"

int cm_group_get(char *group, cm_group *g) {
	int i;
	struct group *gr = malloc(sizeof(struct stat));
	if((i = cm_group_get_state(group, gr)) < 0) {
		goto cleanup;
	} else {
		g->state = i;
	}
	if(g->state == CM_PRESENT) {
		g->gid = (int)gr->gr_gid;
		if((i = cm_group_get_passwd(gr, &g->passwd)) < 0) {
			goto cleanup;
		}
	}
	free(gr);
	return 0;
cleanup:
	free(gr);
	return i;
}
