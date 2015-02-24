#include <stdlib.h>
#include <string.h>
#include "common.h"

int cm_join_members(char **mem, char *buf) {
	int i, j, l = 0;
	for (i = 0; mem[i] != NULL; i++) {
		if(i != 0) {
			memcpy(buf + l, ",", 1);
			l += 1;
		}
		j = strlen(mem[i]);
		memcpy(buf + l, mem[i], j);
		l += j;
	}
	memcpy(buf + l, "\0", 1);
	return 0;
}
