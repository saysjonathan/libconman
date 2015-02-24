#ifndef _CM_GROUP_H
#define _CM_GROUP_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct cm_group cm_group;
struct cm_group {
	int state;
	int gid;
	char *passwd;
};

int cm_group_init(cm_group *g);
int cm_group_get(char *group, cm_group *g);
int cm_group_set(char *group, cm_group *g);
void cm_group_deinit(cm_group *g);

#ifdef __cplusplus
}
#endif
#endif
