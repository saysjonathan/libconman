#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

static int compare(const void *a, const void *b) {
	return *(int *)a < *(int *)b;
}

int cm_find_next_id(char *file, char *pattern) {
	char buf[2048];
	size_t bs = sizeof(buf);
	int a[512], i, gid;
	FILE *f;
	errno = 0;
	if((f = fopen(file, "r")) == NULL) {
		return -errno;
	}
	i = 0;
	while(fgets(buf, bs, f) != NULL) {
		if(sscanf(buf, pattern, &gid) != EOF) {
			a[i] = gid;
		}
		i++;
	}
	fclose(f);
	qsort(&a[0], i, sizeof(int), &compare);
	return a[0]+1;
}
