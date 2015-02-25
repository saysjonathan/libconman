#ifndef _CM_UTIL_IMPL
#define _CM_UTIL_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <sys/stat.h>
#include "conman/error.h"
#include "conman/state.h"

int cm_get_owner(struct stat *s, char **owner);
int cm_get_group(struct stat *s, char **group);
int cm_get_mode(struct stat *s, char **mode);
int cm_set_owner(char *path, char *owner);
int cm_set_group(char *path, char *group);
int cm_set_mode(char *path, char *mode);

int cm_append_entry(char *line, size_t size, char *file);
int cm_delete_entry(char *name, char *pattern, char *file, char *tmpfile);
int cm_replace_entry(char *name, char *pattern, char *line, char *file, char *tmpfile);
int cm_find_next_id(char *file, char *pattern);
int cm_join_members(char **mem, char *buf);

#ifdef __cplusplus
}
#endif
#endif