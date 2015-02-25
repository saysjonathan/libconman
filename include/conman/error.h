#ifndef _CM_ERROR_H
#define _CM_ERROR_H
#ifdef __cplusplus
extern "C" {
#endif

enum cm_error {
	CM_ERR_MISSING		= -256,
	CM_ERR_NOUSR 		= -257,
	CM_ERR_NOGRP 		= -258,
	CM_ERR_NOTFILE		= -259,
	CM_ERR_NOTDIR		= -260,
	CM_ERR_NOTLINK		= -261,
	CM_ERR_NOTRGT		= -262,
	CM_ERR_GIDEXISTS	= -263,
	CM_ERR_UIDEXISTS	= -264,
};

char *cm_strerror(int e);

#ifdef __cplusplus
}
#endif
#endif
