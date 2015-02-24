#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "group.h"

static int addgroup(char *group, int gid, char *passwd) {
	int i;
	static char buf[512];
	size_t n;
	if(passwd[0] == '\0') {
		passwd = "x";
	}
	n = snprintf(buf, sizeof(buf), "%s:%s:%d:\n", group, passwd, gid);
	if((i = cm_append_entry(buf, n, GROUPFILE)) != 0) {
		return i;
	}
	return 0;
}

static int addgshadow(char *group, char *passwd) {
	int i;
	static char buf[512];
	size_t n;
	if(passwd[0] == '\0') {
		passwd = "!";
	}
	n = snprintf(buf, sizeof(buf), "%s:%s::\n", group, passwd);
	if((i = cm_append_entry(buf, n, GSHADOWFILE)) != 0) {
		return i;
	}
	return 0;
}

static int creategroup(char *group, int gid, char *passwd) {
	int i;
	if(gid != 0) {
		struct group *g = getgrgid(gid);
		if(g != NULL) {
			return CM_ERR_GIDEXISTS;
		}
	}
	if(gid == 0) {
		gid = cm_find_next_id(GROUPFILE, "%*[^:]:%*[^:]:%d:%*[^:]");
	}
	if((i = addgroup(group, gid, passwd)) != 0) {
		return i;
	}
	if((i = addgshadow(group, passwd)) != 0) {
		return i;
	}
	return 0;
}

static int delgroup(char *group) {
	int i;
	if((i = cm_delete_entry(group, "%[^:]:%*[^:]:%*d:%*[^:]", GROUPFILE, TMPGROUPFILE)) != 0) {
		return i;
	}
	return 0;
}

static int delgshadow(char *group) {
	int i;
	if((i = cm_delete_entry(group, "%[^:]:%*[^:]:%*d:%*[^:]", GSHADOWFILE, TMPGSHADOWFILE)) != 0) {
		return i;
	}
	return 0;
}

static int removegroup(char *group) {
	int i;
	if((i = delgroup(group)) != 0) {
		return i;
	}
	if((i = delgshadow(group)) != 0) {
		return i;
	}
	return 0;
}

int cm_group_set_state(char *group, int gid, char *passwd, int state) {
	if(state == CM_PRESENT) {
		return creategroup(group, gid, passwd);
	} else if(state == CM_ABSENT) {
		return removegroup(group);
	}
	return -1;
}
