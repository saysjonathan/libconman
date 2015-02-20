#include <stdlib.h>
#include <string.h>
#include "link.h"

int cm_link_set(char *path, cm_link *l) {
	int i;
	cm_link *c = malloc(sizeof(cm_link));
	if((i = cm_link_init(c)) < 0) {
		free(c);
		return i;
	}
	if((i = cm_link_get(path, c)) < 0) {
		goto cleanup;
	}
	if(l->state != c->state) {
		if((i = cm_link_set_state(path, l->state, l->target)) < 0) {
			goto cleanup;
		}
	}
	if(l->state == CM_PRESENT) {
		if(strlen(l->target) != 0 && strcmp(l->target, c->target) != 0) {
			if((i = cm_link_set_target(path, l->target)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(l->owner) != 0) {
			if((i = cm_set_owner(path, l->owner)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(l->group) != 0) {
			if((i = cm_set_group(path, l->group)) < 0) {
				goto cleanup;
			}
		}
	}
	cm_link_deinit(c);
	free(c);
	return 0;
cleanup:
	cm_link_deinit(c);
	free(c);
	return i;
}
