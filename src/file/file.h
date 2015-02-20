#ifndef _CM_FILE_IMPL
#define _CM_FILE_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include "conman/error.h"
#include "conman/file.h"
#include "conman/state.h"

int cm_file_get_state(char *path, struct stat *s);
int cm_file_get_owner(struct stat *s, char **owner);
int cm_file_get_group(struct stat *s, char **group);
int cm_file_get_mode(struct stat *s, char **mode);

int cm_file_set_state(char *path, int state);
int cm_file_set_owner(char *path, char *owner);
int cm_file_set_group(char *path, char *group);
int cm_file_set_mode(char *path, char *mode);

#ifdef __cplusplus
}
#endif
#endif
