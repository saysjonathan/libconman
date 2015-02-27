#include <stdlib.h>
#include "pkg.h"

int cm_pkg_set(char *pkg, cm_pkg *p) {
	int i;
	cm_pkg *c = malloc(sizeof(cm_pkg));
	if((i = cm_pkg_init(c)) < 0) {
		free(c);
		return i;
	}
	if((i = cm_pkg_get(pkg, c)) < 0) {
		goto cleanup;
	}
	if(p->state != c->state) {
		if((i = cm_pkg_set_state(pkg, p->state)) < 0) {
			goto cleanup;
		}
	}
	goto cleanup;
cleanup:
	cm_pkg_deinit(c);
	free(c);
	return i;
}
