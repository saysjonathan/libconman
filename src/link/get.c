#include <stdlib.h>
#include <sys/stat.h>
#include "link.h"

int cm_link_get(char *path, cm_link *l) {
	int i;
	struct stat *s = malloc(sizeof(struct stat));
	if((i = cm_link_get_state(path, s)) < 0) {
		goto cleanup;
	} else {
		l->state = i;
	}
	if(l->state == CM_PRESENT) {
		if((i = cm_link_get_target(path, &l->target)) < 0) {
			goto cleanup;
		}
		if((i = cm_get_owner(s, &l->owner)) < 0) {
			goto cleanup;
		}
		if((i = cm_get_group(s, &l->group)) < 0) {
			goto cleanup;
		}
	}
	free(s);
	return 0;
cleanup:
	free(s);
	return i;
}
