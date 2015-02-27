#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "yum.h"

static int runcmd(char *cmd) {
	char buf[2048];
	size_t bs = sizeof(buf);
	FILE *f;

	errno = 0;
	if((f = popen(cmd, "r")) == NULL) {
		return -errno;
	}
	while(fgets(buf, bs, f) != NULL) {
		printf("%s", buf);
	}
	return fclose(f);
}

static int createcmd(char *cmd, char *pkg, char **buf) {
	char s[256];
	strcpy(s, cmd);
	strcat(s, " ");
	strcat(s, pkg);
	strncpy(*buf, s, strlen(s));
	return 0;
}

static int install(char *pkg) {
	char *buf;
	buf = malloc(256);
	buf[0] = '\0';
	int i = 0;

	if((i = createcmd(INSTALL_COMMAND, pkg, &buf)) != 0) {
		goto cleanup;
	}
	if((i = runcmd(buf)) != 0) {
		switch(i) {
			case 256:
				i = CM_ERR_NOPKG;
				break;
		}
		goto cleanup;
	}
	goto cleanup;
cleanup:
	free(buf);
	return i;
}

static int uninstall(char *pkg) {
	char *buf;
	buf = malloc(256);
	buf[0] = '\0';
	int i = 0;

	if((i = createcmd(REMOVE_COMMAND, pkg, &buf)) != 0) {
		goto cleanup;
	}
	if((i = runcmd(buf)) != 0) {
		goto cleanup;
	}
	goto cleanup;
cleanup:
	free(buf);
	return i;
}

int cm_pkg_set_state(char *path, int state) {
	if(state == CM_PRESENT) {
		return install(path);
	} else if(state == CM_ABSENT) {
		return uninstall(path);
	}
	return -1;
}
