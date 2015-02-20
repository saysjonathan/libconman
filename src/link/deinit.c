#include <stdlib.h>
#include "link.h"

void cm_link_deinit(cm_link *l) {
	if(l->target) {
		free(l->target);
	}
	if(l->owner) {
		free(l->owner);
	}
	if(l->group) {
		free(l->group);
	}
}
