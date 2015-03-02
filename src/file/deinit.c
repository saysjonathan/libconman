#include <stdlib.h>
#include "file.h"

void cm_file_deinit(cm_file *f) {
	free(f->owner);
	free(f->group);
	free(f->mode);
	free(f->hash);
	free(f->source);
}
