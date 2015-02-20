#include "conman/error.h"
#include <stdlib.h>
#include <string.h>

#define CM_E(a,b) ((int)a),
static int errid[] = {
#include "error.h"
};

#undef CM_E
#define CM_E(a,b) b "\0"
static const char errmsg[] =
#include "error.h"
;

char *cm_strerror(int e) {
	const char *s;
	int i, f = -1;
	int len = sizeof(errid)/sizeof(const char);
	for(i = 0; i < len; i++) {
		if(errid[i] == e) {
			f = i;
		}
	}
	if(f == -1) {
		s = strerror(abs(e));
	} else {
		for (s=errmsg; f; s++, f--) for (; *s; s++);
	}
	return (char *)s;
}
