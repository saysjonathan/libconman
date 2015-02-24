#ifndef _CM_GROUP_IMPL
#define _CM_GROUP_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include <grp.h>
#include <limits.h>
#include "conman/error.h"
#include "conman/group.h"
#include "conman/state.h"
#include "../common/common.h"

#define MAX_GROUP_LEN 16
#define MAX_GROUP_ID UINT_MAX
#define MAX_NGROUP UINT_MAX
#define GROUPFILE "/etc/group"
#define TMPGROUPFILE "/etc/.group.cm"
#define GSHADOWFILE "/etc/gshadow"
#define TMPGSHADOWFILE "/etc/.gshadow.cm"

int cm_group_get_state(char *group, struct group *gr);
int cm_group_get_passwd(struct group *gr, char **passwd);
int cm_group_set_state(char *group, int gid, char *passwd, int state);
int cm_group_set_gid(char *group, int gid);

#ifdef __cplusplus
}
#endif
#endif
