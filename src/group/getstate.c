#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "group.h"

int cm_group_get_state(char *group, struct group *gr) {
	errno = 0;
	struct group *o = getgrnam(group);
	if(o == NULL) {
		if(errno != 0) {
			return -errno;
		}
		return CM_ABSENT;
	} else {
		memcpy(gr, o, sizeof(*o));
		return CM_PRESENT;
	}
}
