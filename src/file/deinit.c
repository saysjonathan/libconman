#include <stdlib.h>
#include "file.h"

void cm_file_deinit(cm_file *f) {
	if(f->owner) {
		free(f->owner);
	}
	if(f->group) {
		free(f->group);
	}
	if(f->mode) {
		free(f->mode);
	}
}
