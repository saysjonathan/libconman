#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int cm_file_get_hash(char *path, char **hash) {
	int i;
	uint8_t md[SHA1_DIGEST_LENGTH];
	char buf[256], r[40], t[40];
	size_t n;
	FILE *f;
	struct sha1 *s = malloc(sizeof(struct sha1));

	sha1_init(s);
	errno = 0;
	if((f = fopen(path, "r")) == NULL) {
		return -errno;
	}
	 while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
		sha1_update(s, buf, n);
	}
	sha1_sum(s, md);
	r[0] = '\0';
	for(i = 0; i < SHA1_DIGEST_LENGTH; i++) {
		n = sprintf(t, "%0x", md[i]);
		strcat(r, t);
	}
	strncpy(*hash, r, strlen(r));
	fclose(f);
	free(s);
	return 0;
}
