#include <stdlib.h>
#include <string.h>
#include "file.h"

static void teardown(cm_file *f) {
	if(f) {
		cm_file_deinit(f);
		free(f);
	}
}

static int setup(char *path, cm_file *f) {
	int i;
	if((i = cm_file_init(f)) < 0) {
		free(f);
		return i;
	}
	if((i = cm_file_get(path, f)) < 0) {
		teardown(f);
		return i;
	}
	return 0;
}

int cm_file_set(char *path, cm_file *f) {
	int i;
	cm_file *c = malloc(sizeof(cm_file));
	cm_file *s = NULL;
	if((i = setup(path, c)) != 0) {
		return i;
	}

	if(f->state != c->state) {
		if((i = cm_file_set_state(path, f->source, f->state)) < 0) {
			goto cleanup;
		}
	}
	if(f->state == CM_PRESENT) {
		if(strlen(f->source) != 0) {
			s = malloc(sizeof(cm_file));
			if((i = setup(f->source, s)) != 0) {
				return i;
			}
			if(strcmp(f->hash, s->hash) != 0) {
				if((i = cm_file_set_state(path, f->source, f->state)) < 0) {
					goto cleanup;
				}
			}
		}
		if(strlen(f->owner) != 0) {
			if((i = cm_set_owner(path, f->owner, 0)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(f->group) != 0) {
			if((i = cm_set_group(path, f->group, 0)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(f->mode) != 0) {
			if((i = cm_set_mode(path, f->mode, 0)) < 0) {
				goto cleanup;
			}
		}
	}
	goto cleanup;
cleanup:
	teardown(c);
	teardown(s);
	return i;
}
