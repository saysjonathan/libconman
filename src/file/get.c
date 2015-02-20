#include <stdlib.h>
#include <sys/stat.h>
#include "file.h"

int cm_file_get(char *path, cm_file *f) {
	int i;
	struct stat *s = malloc(sizeof(struct stat));
	if((i = cm_file_get_state(path, s)) < 0) {
		goto cleanup;
	} else {
		f->state = i;
	}
	if(f->state == CM_PRESENT) {
		if((i = cm_get_owner(s, &f->owner)) < 0) {
			goto cleanup;
		}
		if((i = cm_get_group(s, &f->group)) < 0) {
			goto cleanup;
		}
		if((i = cm_get_mode(s, &f->mode)) < 0) {
			goto cleanup;
		}
	}
	free(s);
	return 0;
cleanup:
	free(s);
	return i;
}
