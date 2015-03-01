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
	int s;
	package = pkg;
	state = CM_ABSENT;
	if((s = cm_run_cmd(RPM_PATH, args, parse_query)) != 0) {
		return s;
	}
	return state;
}
