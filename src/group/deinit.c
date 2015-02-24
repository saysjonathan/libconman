#include <stdlib.h>
#include "group.h"

void cm_group_deinit(cm_group *g) {
	if(g->passwd) {
		free(g->passwd);
	}
}
