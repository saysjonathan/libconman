#include <errno.h>
#include <string.h>
#include "user.h"

int cm_user_get_state(char *user, struct passwd *pw) {
	struct passwd *o = getpwnam(user);
	errno = 0;
	if(o == NULL) {
		if(errno != 0) {
			return -errno;
		}
		return CM_ABSENT;
	} else {
		memcpy(pw, o, sizeof(*o));
		return CM_PRESENT;
	}
}
