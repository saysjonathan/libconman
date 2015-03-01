#ifndef _CM_PKG_IMPL
#define _CM_PKG_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include "conman/error.h"
#include "conman/pkg.h"
#include "conman/state.h"
#include "../common/common.h"

#define MAX_PKGVER_LEN	64

int cm_pkg_get_state(char *pkg, cm_pkg *p);
int cm_pkg_set_state(char *path, int state);

#ifdef __cplusplus
}
#endif
#endif
