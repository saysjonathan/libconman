#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yum.h"

static int parse(const char *s) {
	return 0;
}

static int install(char *pkg) {
	int i;
	char * const args[] = {
		RPM_PATH,
		"install",
		"-d 0",
		"-e 0",
		"-y",
		pkg,
		NULL,
	};
	if((i = cm_run_cmd(YUM_PATH, args, parse)) != 0) {
		return CM_ERR_NOPKG;
	}
	return 0;
}

static int uninstall(char *pkg) {
	char * const args[] = {
		RPM_PATH,
		"remove",
		"-d 0",
		"-e 0",
		"-y",
		pkg,
		NULL,
	};
	return cm_run_cmd(YUM_PATH, args, parse);
}

int cm_pkg_set_state(char *path, int state) {
	if(state == CM_PRESENT) {
		return install(path);
	} else if(state == CM_ABSENT) {
		return uninstall(path);
	}
	return -1;
}
