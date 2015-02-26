#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"

int cm_link_init(cm_link *l) {
	errno = 0;
	if((l->target = malloc(256)) == NULL) {
		return -errno;
	}
	l->target[0] = '\0';
	if((l->owner = malloc(LOGIN_NAME_MAX)) == NULL) {
		return -errno;
	}
	l->owner[0] = '\0';
	if((l->group = malloc(LOGIN_NAME_MAX)) == NULL) {
		return -errno;
	}
	l->group[0] = '\0';
	return 0;
}
