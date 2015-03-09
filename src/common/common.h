#ifndef _CM_UTIL_IMPL
#define _CM_UTIL_IMPL
#ifdef __cplusplus
extern "C" {
#endif

#ifndef LOGIN_NAME_MAX
#define LOGIN_NAME_MAX 256
#endif
#define OWNER_NAME_MAX LOGIN_NAME_MAX 
#define GROUP_NAME_MAX LOGIN_NAME_MAX 

#include <stdlib.h>
#include <stdint.h>
#include <sys/stat.h>
#include "conman/error.h"
#include "conman/state.h"

struct sha1 {
	uint64_t len;
	uint32_t h[5];
	uint8_t buf[64];
};

enum { SHA1_DIGEST_LENGTH = 20 };

void sha1_init(void *ctx);
void sha1_update(void *ctx, const void *m, unsigned long len);
void sha1_sum(void *ctx, uint8_t md[SHA1_DIGEST_LENGTH]);

int cm_recurse(char *path, char *arg, int (*fn)(char *, char *, int));
int cm_rm(char *path, char *unused, int recurse);

int cm_get_owner(struct stat *s, char **owner);
int cm_get_group(struct stat *s, char **group);
int cm_get_mode(struct stat *s, char **mode);
int cm_set_owner(char *path, char *owner, int recurse);
int cm_set_group(char *path, char *group, int recurse);
int cm_set_mode(char *path, char *mode, int recurse);

int cm_append_entry(char *line, size_t size, char *file);
int cm_delete_entry(char *name, char *pattern, char *file, char *tmpfile);
int cm_replace_entry(char *name, char *pattern, char *line, char *file, char *tmpfile);
int cm_find_next_id(char *file, char *pattern);
int cm_join_members(char **mem, char *buf);

int cm_run_cmd(char *path, char * const args[], int (*fn)(const char *));

#ifdef __cplusplus
}
#endif
#endif
