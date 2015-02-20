#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include "dir.h"

int cm_dir_init(cm_dir *d) {
	errno = 0;
	if((d->owner = malloc(LOGIN_NAME_MAX)) == NULL) {
		return -errno;
	}
	d->owner[0] = '\0';
	if((d->group = malloc(LOGIN_NAME_MAX)) == NULL) {
		return -errno;
	}
	d->group[0] = '\0';
	if((d->mode = malloc(4)) == NULL) {
		return -errno;
	}
	d->mode[0] = '\0';
	return 0;
}
