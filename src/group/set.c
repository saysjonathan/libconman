#include <stdlib.h>
#include "group.h"

int cm_group_set(char *group, cm_group *g) {
	int i;
	cm_group *c = malloc(sizeof(cm_group));
	if((i = cm_group_init(c)) < 0) {
		free(c);
		return i;
	}
	if((i = cm_group_get(group, c)) < 0) {
		goto cleanup;
	}
	if(g->state != c->state) {
		if((i = cm_group_set_state(group, g->gid, g->passwd, g->state)) < 0) {
			goto cleanup;
		}
	}
	if(g->state == CM_PRESENT) {
		if((g->gid != 0) && (g->gid != c->gid)) {
			if((i = cm_group_set_gid(group, g->gid)) < 0) {
				goto cleanup;
			}
		}
	}
cleanup:
	cm_group_deinit(c);
	free(c);
	return i;
}
