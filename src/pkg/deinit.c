#include <stdlib.h>
#include "pkg.h"

void cm_pkg_deinit(cm_pkg *p) {
	free(p->version);
}
