#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int cm_file_init(cm_file *f) {
	errno = 0;
	if((f->owner = malloc(OWNER_NAME_MAX)) == NULL) {
		return -errno;
	}
	f->owner[0] = '\0';
	if((f->group = malloc(GROUP_NAME_MAX)) == NULL) {
		return -errno;
	}
	f->group[0] = '\0';
	if((f->mode = malloc(4)) == NULL) {
		return -errno;
	}
	f->mode[0] = '\0';
	if((f->source = malloc(256)) == NULL) {
		return -errno;
	}
	f->source[0] = '\0';
	if((f->hash = malloc(42)) == NULL) {
		return -errno;
	}
	f->hash[0] = '\0';
	return 0;
}
