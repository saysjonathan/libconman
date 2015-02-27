#include <stdlib.h>
#include <string.h>
#include "dir.h"

int cm_dir_set(char *path, cm_dir *d) {
	int i;
	cm_dir *c = malloc(sizeof(cm_dir));
	if((i = cm_dir_init(c)) < 0) {
		free(c);
		return i;
	}
	if((i = cm_dir_get(path, c)) < 0) {
		goto cleanup;
	}
	if(d->state != c->state) {
		if((i = cm_dir_set_state(path, d->state, d->recurse)) < 0) {
			goto cleanup;
		}
	}
	if(d->state == CM_PRESENT) {
		if(strlen(d->owner) != 0) {
			if((i = cm_set_owner(path, d->owner)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(d->group) != 0) {
			if((i = cm_set_group(path, d->group)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(d->mode) != 0) {
			if((i = cm_set_mode(path, d->mode)) < 0) {
				goto cleanup;
			}
		}
	}
	goto cleanup;
cleanup:
	cm_dir_deinit(c);
	free(c);
	return i;
}
