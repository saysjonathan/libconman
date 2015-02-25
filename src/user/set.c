#include <stdlib.h>
#include <string.h>
#include "user.h"

int cm_user_set(char *user, cm_user *u) {
	int i = 0;
	cm_user *c = malloc(sizeof(cm_user));
	if((i = cm_user_init(c)) < 0) {
		free(c);
		return i;
	}
	if((i = cm_user_get(user, c)) < 0) {
		goto cleanup;
	}
	if(u->state != c->state) {
		if((i = cm_user_set_state(user, u)) < 0) {
			goto cleanup;
		}
	}
	if(u->state == CM_PRESENT && c->state == CM_PRESENT) {
		if(strlen(u->passwd) != 0) {
			if((i = cm_user_set_passwd(user, u->passwd)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(u->group) != 0) {
			if((i = cm_user_set_group(user, u->group)) < 0) {
				goto cleanup;
			}
		}
		if(strcmp(u->comment, c->comment) != 0) {
			if((i = cm_user_set_comment(user, u->comment)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(u->homedir) != 0) {
			if((i = cm_user_set_homedir(user, u->homedir)) < 0) {
				goto cleanup;
			}
		}
		if(strlen(u->shell) != 0) {
			if((i = cm_user_set_shell(user, u->shell)) < 0) {
				goto cleanup;
			}
		}
	}
	goto cleanup;
cleanup:
	cm_user_deinit(c);
	free(c);
	return i;
}
