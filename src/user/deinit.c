#include <stdlib.h>
#include "user.h"

void cm_user_deinit(cm_user *u) {
	if(u->passwd) {
		free(u->passwd);
	}
	if(u->comment) {
		free(u->comment);
	}
	if(u->homedir) {
		free(u->homedir);
	}
	if(u->shell) {
		free(u->shell);
	}
}
