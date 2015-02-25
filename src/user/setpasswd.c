#include <errno.h>
#include <shadow.h>
#include <stdio.h>
#include <time.h>
#include "user.h"

int cm_user_set_passwd(char *user, char *passwd) {
	int i, day;
	static char buf[2048];
	day = time(NULL)/86400;

	errno = 0;
	struct spwd *s = getspnam(user);
	if(s == NULL) {
		return -errno;
	}
	snprintf(buf, sizeof(buf), "%s:%s:%d:%ld:%ld:%ld:::\n",
		user, passwd, day, s->sp_min, s->sp_max, s->sp_warn);
	if((i = cm_replace_entry(user, "%[^:]:%*[^:]:%*d:%*d:%*d:%*d:%*d:%*d:%*d", buf, SHADOWFILE, TMPSHADOWFILE)) != 0) {
		return i;
	}
	return 0;
}
