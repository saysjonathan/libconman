#ifndef _CM_FILE_IMPL
#define _CM_FILE_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include <sys/stat.h>
#include "conman/error.h"
#include "conman/file.h"
#include "conman/state.h"
#include "../common/common.h"

int cm_file_get_state(char *path, struct stat *s);
int cm_file_get_hash(char *path, char **hash);
int cm_file_set_state(char *path, char *source, int state);

#ifdef __cplusplus
}
#endif
#endif
