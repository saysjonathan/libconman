#include <errno.h>
#include <stdlib.h>
#include "pkg.h"

int cm_pkg_init(cm_pkg *p) {
	errno = 0;
	if((p->version = malloc(sizeof(MAX_PKGVER_LEN))) == NULL) {
		return -errno;
	}
	p->version[0] = '\0';
	return 0;
}
