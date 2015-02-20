#include <stdlib.h>
#include <sys/stat.h>
#include "dir.h"

int cm_dir_get(char *path, cm_dir *d) {
	int i;
	struct stat *s = malloc(sizeof(struct stat));
	if((i = cm_dir_get_state(path, s)) < 0) {
		goto cleanup;
	} else {
		d->state = i;
	}
	if(d->state == CM_PRESENT) {
		if((i = cm_get_owner(s, &d->owner)) < 0) {
			goto cleanup;
		}
		if((i = cm_get_group(s, &d->group)) < 0) {
			goto cleanup;
		}
		if((i = cm_get_mode(s, &d->mode)) < 0) {
			goto cleanup;
		}
	}
	free(s);
	return 0;
cleanup:
	free(s);
	return i;
}
