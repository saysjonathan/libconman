#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "yum.h"

int cm_pkg_get_state(char *pkg, cm_pkg *p) {
	char buf[MAX_RPMQA_LEN], pm[256], vm[256];
	size_t bs = sizeof(buf);
	int s = CM_ABSENT;
	FILE *f;

	errno = 0;
	if((f = popen(QUERY_COMMAND, "r")) == NULL) {
		return -errno;
	}
	while(fgets(buf, bs, f) != NULL) {
		if(sscanf(buf, "%s %*s %s %*s %*s %*s", pm, vm) != EOF) {
			if(strcmp(pkg, pm) == 0) {
				s = CM_PRESENT;
			}
		}
	}
	fclose(f);
	return s;
}
