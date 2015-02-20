#include <stdlib.h>
#include "dir.h"

void cm_dir_deinit(cm_dir *d) {
	if(d->owner) {
		free(d->owner);
	}
	if(d->group) {
		free(d->group);
	}
	if(d->mode) {
		free(d->mode);
	}
}
