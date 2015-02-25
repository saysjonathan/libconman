#ifndef _CM_USER_H
#define _CM_USER_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct cm_user cm_user;
struct cm_user {
	int state;
	char *passwd;
	int uid;
	char *group;
	char *comment;
	char *homedir;
	char *shell;
};

int cm_user_init(cm_user *u);
int cm_user_get(char *user, cm_user *u);
int cm_user_set(char *user, cm_user *u);
void cm_user_deinit(cm_user *u);

#ifdef __cplusplus
}
#endif
#endif
