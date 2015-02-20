#ifndef _CM_UTIL_IMPL
#define _CM_UTIL_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include "conman/error.h"
#include "conman/state.h"

int cm_get_owner(struct stat *s, char **owner);
int cm_get_group(struct stat *s, char **group);
int cm_get_mode(struct stat *s, char **mode);
int cm_set_owner(char *path, char *owner);
int cm_set_group(char *path, char *group);
int cm_set_mode(char *path, char *mode);

#ifdef __cplusplus
}
#endif
#endif
