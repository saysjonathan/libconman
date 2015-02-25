#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

static int shadowpass(char *user, char **passwd) {
	char buf[2048], u[256], p[256];
	size_t bs = sizeof(buf);
	FILE *f;

	errno = 0;
	if((f = fopen(SHADOWFILE, "r")) == NULL) {
		return -errno;
	}
	while(fgets(buf, bs, f) != NULL) {
		if(sscanf(buf, "%[^:]:%[^:]:%*[^:]:%*[^:]:%*[^:]:%*[^:]:%*[^:]:%*[^:]:%*[^:]", u, p) != EOF) {
			if(strcmp(u, user) == 0) {
				strncpy(*passwd, p, sizeof(p));
				break;
			}
		}
	}
	fclose(f);
	return 0;
}

int cm_user_get_passwd(struct passwd *pw, char **passwd) {
	int i;
	errno = 0;
	if(strcmp(pw->pw_passwd, "x") == 0) {
		if((i = shadowpass(pw->pw_name, passwd)) != 0) {
			return i;
		}
	}
	return -errno;
}
