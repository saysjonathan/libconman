#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "common.h"

int cm_replace_entry(char *name, char *pattern, char *line, char *file, char *tmpfile) {
	char buf[2048], match[256];
	size_t bs = sizeof(buf);
	int i;
	FILE *o, *n;
	struct stat s;

	errno = 0;
	if((o = fopen(file, "r")) == NULL) {
		return -errno;
	}
	if((n = fopen(tmpfile, "w")) == NULL) {
		fclose(o);
		return -errno;
	}
	while(fgets(buf, bs, o) != NULL) {
		if(sscanf(buf, pattern, match) != EOF) {
			if(strcmp(name, match) == 0) {
				if(fprintf(n, line) == -1) {
					goto cleanup;
				}
			} else {
				if(fprintf(n, buf) == -1) {
					goto cleanup;
				}
			}
		}
	}
	if((i = stat(file, &s)) == -1) {
		goto cleanup;
	}
        if((i = chown(tmpfile, s.st_uid, s.st_gid)) != 0) {
                goto cleanup;
        }
        if((i = chmod(tmpfile, s.st_mode)) != 0) {
                goto cleanup;
        }
        if(rename(tmpfile, file) != 0) {
                goto cleanup;
        }
        fclose(o);
        fclose(n);
        return 0;
cleanup:
	fclose(o);
	fclose(n);
	return -errno;
}
