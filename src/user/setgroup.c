#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include "user.h"

int cm_user_set_group(char *user, char *group) {
	int i;
	static char buf[2048];

	errno = 0;
	struct group *g = getgrnam(group);
	if(g == NULL) {
		return CM_ERR_NOGRP;
	}
	struct passwd *p = getpwnam(user);
	if(p == NULL) {
		return CM_ERR_NOUSR;
	}
	snprintf(buf, sizeof(buf), "%s:%s:%d:%d:%s:%s:%s\n",
		user, p->pw_passwd, p->pw_uid, (int)g->gr_gid,
		p->pw_gecos, p->pw_dir, p->pw_shell);
	if((i = cm_replace_entry(user, "%[^:]:%*[^:]:%*d:%*d:%*[^:]:%*[^:]:%*[^:]", buf, PASSWDFILE, TMPPASSWDFILE)) != 0) {
		return i;
	}
	return 0;
}
