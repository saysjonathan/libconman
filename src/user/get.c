#include <stdlib.h>
#include <string.h>
#include "user.h"

int cm_user_get(char *user, cm_user *u) {
	int i;
	struct passwd *pw = malloc(sizeof(struct passwd));
	if((i = cm_user_get_state(user, pw)) < 0) {
		goto cleanup;
	} else {
		u->state = i;
	}
	if(u->state == CM_PRESENT) {
		u->uid = (int)pw->pw_uid;
		if((i = cm_user_get_passwd(pw, &u->passwd)) < 0) {
			goto cleanup;
		}
		if((i = cm_user_get_group(pw, &u->group)) < 0) {
			goto cleanup;
		}
		strncpy(u->comment, pw->pw_gecos, MAX_COMMENT_LEN);
		strncpy(u->homedir, pw->pw_dir, MAX_HOMEDIR_LEN);
		strncpy(u->shell, pw->pw_shell, MAX_SHELL_LEN);
	}
	free(pw);
	return 0;
cleanup:
	free(pw);
	return i;
}
