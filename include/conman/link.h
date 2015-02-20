#ifndef _CM_LINK_H
#define _CM_LINK_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct cm_link cm_link;
struct cm_link {
	int state;
	char *target;
	char *owner;
	char *group;
};

int cm_link_init(cm_link *l);
int cm_link_get(char *path, cm_link *l);
int cm_link_set(char *path, cm_link *l);
void cm_link_deinit(cm_link *l);

#ifdef __cplusplus
}
#endif
#endif
