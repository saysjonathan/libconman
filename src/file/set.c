#include <stdlib.h>
#include <string.h>
#include "file.h"

int cm_file_set(char *path, cm_file *f) {
	int i;
	cm_file *c = malloc(sizeof(cm_file));
	if((i = cm_file_init(c)) < 0) {
		free(c);
		return i;
	}
	if((i = cm_file_get(path, c)) < 0) {
		goto cleanup;
	}
	if(f->state != c->state) {
		if((i = cm_file_set_state(path, f->state)) < 0) {
			goto cleanup;
		}
	}
	if(f->state == CM_PRESENT) {
		if(strlen(f->owner) != 0) {
			if((i = cm_set_owner(path, f->owner)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(f->group) != 0) {
			if((i = cm_set_group(path, f->group)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(f->mode) != 0) {
			if((i = cm_set_mode(path, f->mode)) < 0) {
				goto cleanup;
			}
		}
	}
	cm_file_deinit(c);
	free(c);
	return 0;
cleanup:
	cm_file_deinit(c);
	free(c);
	return i;
}
