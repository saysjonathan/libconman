#ifndef _CM_PKG_H
#define _CM_PKG_H
#ifdef __cplusplus
extern "C" {
#endif

typedef struct cm_pkg cm_pkg;
struct cm_pkg {
	int state;
	char *version;
};

int cm_pkg_init(cm_pkg *p);
int cm_pkg_get(char *pkg, cm_pkg *p);
int cm_pkg_set(char *pkg, cm_pkg *p);
void cm_pkg_deinit(cm_pkg *p);

#ifdef __cplusplus
}
#endif
#endif
