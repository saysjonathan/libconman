#ifndef _CM_FILE_H
#define _CM_FILE_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct cm_file cm_file;
struct cm_file {
	int state;
	char *owner;
	char *group;
	char *mode;
};

int cm_file_init(cm_file *f);
int cm_file_get(char *path, cm_file *f);
int cm_file_set(char *path, cm_file *f);
void cm_file_deinit(cm_file *f);

#ifdef __cplusplus
}
#endif
#endif
