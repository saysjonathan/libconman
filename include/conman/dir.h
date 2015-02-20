#ifndef _CM_DIR_H
#define _CM_DIR_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct cm_dir cm_dir;
struct cm_dir {
	int state;
	char *owner;
	char *group;
	char *mode;
};

int cm_dir_init(cm_dir *d);
int cm_dir_get(char *path, cm_dir *d);
int cm_dir_set(char *path, cm_dir *d);
void cm_dir_deinit(cm_dir *d);

#ifdef __cplusplus
}
#endif
#endif
