#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

int cm_user_init(cm_user *u) {
	errno = 0;
	if((u->passwd = malloc(MAX_PASSWD_LEN)) == NULL) {
		return -errno;
	}
	u->passwd[0] = '\0';
	if((u->group = malloc(MAX_PASSWD_LEN)) == NULL) {
		return -errno;
	}
	u->group[0] = '\0';
	if((u->comment = malloc(MAX_COMMENT_LEN)) == NULL) {
		return -errno;
	}
	u->comment[0] = '\0';
	if((u->homedir = malloc(MAX_HOMEDIR_LEN)) == NULL) {
		return -errno;
	}
	u->homedir[0] = '\0';
	if((u->shell = malloc(MAX_SHELL_LEN)) == NULL) {
		return -errno;
	}
	u->shell[0] = '\0';
	return 0;
}
