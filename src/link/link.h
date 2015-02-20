#ifndef _CM_LINK_IMPL
#define _CM_LINK_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include "conman/error.h"
#include "conman/link.h"
#include "conman/state.h"
#include "../common/common.h"

int cm_link_get_state(char *path, struct stat *s);
int cm_link_get_target(char *path, char **target);
int cm_link_set_state(char *path, int state, char *target);
int cm_link_set_target(char *path, char *target);
int cm_link_set_owner(char *path, char *owner);
int cm_link_set_group(char *path, char *group);

#ifdef __cplusplus
}
#endif
#endif
