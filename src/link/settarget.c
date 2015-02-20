#include <errno.h>
#include "link.h"

int cm_link_set_target(char *path, char *target) {
	int i;
	if((i = cm_link_set_state(path, CM_ABSENT, target)) != 0) {
		return i;
	}
	if((i = cm_link_set_state(path, CM_PRESENT, target)) != 0) {
		return i;
	}
	return 0;
}
