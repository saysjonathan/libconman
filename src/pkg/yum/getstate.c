#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "yum.h"

static int state;
static char *package;
static char * const args[] = {
	RPM_PATH,
	"-qa",
	"--qf",
	"%{NAME} %{VERSION} %{RELEASE} %{ARCH}\\n",
	NULL,
};

static char * const outdated_args[] = {
	YUM_PATH,
	"check-update",
	NULL
};

static int parse_query(const char *string) {
	char p[256];
	if(sscanf(string, "%s %*s %*s %*s %*s", p) != EOF) {
		if(strcmp(package, p) == 0) {
			state = CM_PRESENT;
			return state;
		}
	}
	return 0;
}

int cm_pkg_get_state(char *pkg, cm_pkg *p) {
	package = pkg;
	state = CM_ABSENT;
	cm_run_cmd(RPM_PATH, args, parse_query);
	if(state == CM_PRESENT) {
		if(cm_run_cmd(YUM_PATH, outdated_args, NULL) != 0) {
			state = CM_OUTDATED;
		} else {
			state = CM_LATEST;
		}
	}
	return state;
}
