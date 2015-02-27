#include "pkg.h"

int cm_pkg_get(char *pkg, cm_pkg *p) {
	int i;
	if((i = cm_pkg_get_state(pkg, p)) < 0) {
		return i;
	} else {
		p->state = i;
	}
	return 0;
}
