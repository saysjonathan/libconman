#include <errno.h>
#include <grp.h>
#include <stdio.h>
#include <string.h>
#include <shadow.h>
#include <time.h>
#include "user.h"

static int addpasswd(char *user, cm_user *u) {
	int i, gid;
	static char buf[2048];
	size_t n;
	struct group *g = getgrnam(u->group);
	gid = (int)g->gr_gid;
	n = snprintf(buf, sizeof(buf), "%s:%s:%d:%d:%s:%s:%s\n",
			user, u->passwd, u->uid, gid, u->comment,
			u->homedir, u->shell);
	if((i = cm_append_entry(buf, n, PASSWDFILE)) != 0) {
		return i;
	}
	return 0;
}

static int addshadow(char *user, cm_user *u) {
	int i, day;
	static char buf[2048];
	size_t n;
	day = time(NULL)/86400;
	n = snprintf(buf, sizeof(buf), "%s:%s:%d:%d:%d:%d:::\n",
			user, u->passwd, day, 0, 99999, 7);
	errno = 0;
	if((i = lckpwdf()) != 0) {
		return -errno;
	}
	if((i = cm_append_entry(buf, n, SHADOWFILE)) != 0) {
		return i;
	}
	if((i = ulckpwdf()) != 0) {
		return -errno;
	}
	return 0;
}

static int delpasswd(char *user) {
	int i;
	if((i = cm_delete_entry(user, "%[^:]:%*[^:]:%*d:%*d:%*[^:]:%*[^:]:%*[^:]", PASSWDFILE, TMPPASSWDFILE)) != 0) {
		return i;
	}
	return 0;
}

static int delshadow(char *user) {
	int i;
	if((i = cm_delete_entry(user, "%[^:]:%*[^:]:%*d:%*d:%*d:%*d:%*d:%*d:%*d", SHADOWFILE, TMPSHADOWFILE)) != 0) {
		return i;
	}
	return 0;
}

static int validate(cm_user *u) {
	if(u->group[0] == '\0') {
		return CM_ERR_MISSING;
	}
	struct group *g = getgrnam(u->group);
	if(g == NULL) {
		return CM_ERR_NOGRP;
	}
	if(u->passwd[0] == '\0') {
		strncpy(u->passwd, "x", 2);
	}
	if(u->homedir[0] == '\0') {
		return CM_ERR_MISSING;
	}
	if(u->shell[0] == '\0') {
		return CM_ERR_MISSING;
	}
	if(u->uid != 0) {
		struct passwd *p = getpwuid(u->uid);
		if(p != NULL) {
			return CM_ERR_UIDEXISTS;
		}
	}
	if(u->uid == 0) {
		u->uid = cm_find_next_id(PASSWDFILE, "%*[^:]:%*[^:]:%d:%*d:%*[^:]:%*[^:]:%*[^:]");
	}
	return 0;
}


static int createuser(char *user, cm_user *u) {
	int i;
	if((i = validate(u)) != 0) {
		return i;
	}
	if((i = addpasswd(user, u)) != 0) {
		return i;
	}
	if((i = addshadow(user, u)) != 0) {
		return i;
	}
	return 0;
}

static int removeuser(char *user) {
	int i;
	if((i = delpasswd(user)) != 0) {
		return i;
	}
	if((i = delshadow(user)) != 0) {
		return i;
	}
	return 0;
}

int cm_user_set_state(char *user, cm_user *u) {
	if(u->state == CM_PRESENT) {
		return createuser(user, u);
	} else if(u->state == CM_ABSENT) {
		return removeuser(user);
	}
	return -1;
}
