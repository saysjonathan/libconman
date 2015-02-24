#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "group.h"

int cm_group_init(cm_group *g) {
	errno = 0;
	if((g->passwd = malloc(MAX_GROUP_LEN)) == NULL) {
		return -errno;
	}
	g->passwd[0] = '\0';
	return 0;
}
