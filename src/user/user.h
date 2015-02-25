#ifndef _CM_USER_IMPL
#define _CM_USER_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include <pwd.h>
#include <limits.h>
#include "conman/error.h"
#include "conman/user.h"
#include "conman/state.h"
#include "../common/common.h"

#define MAX_PASSWD_LEN 	256
#define MAX_COMMENT_LEN 256
#define MAX_HOMEDIR_LEN 256
#define MAX_SHELL_LEN	256

#define PASSWDFILE "/etc/passwd"
#define TMPPASSWDFILE "/etc/.passwd.cm"
#define SHADOWFILE "/etc/shadow"
#define TMPSHADOWFILE "/etc/.shadow.cm"

int cm_user_get_state(char *user, struct passwd *pw);
int cm_user_get_passwd(struct passwd *pw, char **passwd);
int cm_user_get_group(struct passwd *pw, char **group);
int cm_user_set_state(char *user, cm_user *u);
int cm_user_set_passwd(char *user, char *passwd);
int cm_user_set_group(char *user, char *group);
int cm_user_set_comment(char *user, char *group);
int cm_user_set_homedir(char *user, char *homedir);
int cm_user_set_shell(char *user, char *shell);

#ifdef __cplusplus
}
#endif
#endif
