#include <errno.h>
#include <pwd.h>
#include <string.h>
#include <sys/stat.h>
#include "common.h"

int cm_get_owner(struct stat *s, char **owner) {
	size_t bs = OWNER_NAME_MAX;
	errno = 0;
	struct passwd *pw = getpwuid(s->st_uid);
	if(pw == NULL) {
		return -errno;
	}
	strncpy(*owner, pw->pw_name, bs);
	return 0;
}
