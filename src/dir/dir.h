#ifndef _CM_DIR_IMPL
#define _CM_DIR_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include "conman/error.h"
#include "conman/dir.h"
#include "conman/state.h"
#include "../common/common.h"

int cm_dir_get_state(char *path, struct stat *s);
int cm_dir_get_owner(struct stat *s, char **owner);
int cm_dir_get_group(struct stat *s, char **group);
int cm_dir_get_mode(struct stat *s, char **mode);

int cm_dir_set_state(char *path, int state);
int cm_dir_set_owner(char *path, char *owner);
int cm_dir_set_group(char *path, char *group);
int cm_dir_set_mode(char *path, char *mode);

#ifdef __cplusplus
}
#endif
#endif
