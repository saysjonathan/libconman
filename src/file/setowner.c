#include <errno.h>
#include <pwd.h>
#include <unistd.h>
#include "file.h"

int cm_file_set_owner(char *path, char *owner) {
	struct passwd *pw = getpwnam(owner);
	if(pw == NULL) {
		return CM_ERR_NOUSR;
	}
	errno = 0;
	if(chown(path, pw->pw_uid, -1) != 0) {
		return -errno;
	}
	return 0;

}
