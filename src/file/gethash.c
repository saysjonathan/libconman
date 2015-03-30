#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

int cm_file_get_hash(char *path, char **hash) {
	int i;
	uint8_t md[SHA1_DIGEST_LENGTH];
	char buf[256], t[2];
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
	for(i = 0; i < SHA1_DIGEST_LENGTH; i++) {
		n = sprintf(t, "%02x", md[i]);
		strcat(*hash, t);
	}
	fclose(f);
	free(s);
	return 0;
}
