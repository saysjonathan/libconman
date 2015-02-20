#include <errno.h>
#include <pwd.h>
#include <string.h>
#include "file.h"

int cm_file_get_owner(struct stat *s, char **owner) {
	size_t bs = sizeof(*owner);
	errno = 0;
	struct passwd *pw = getpwuid(s->st_uid);
	if(pw == NULL) {
		return -errno;
	}
	strncpy(*owner, pw->pw_name, bs);
	return 0;
}
