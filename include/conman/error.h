#ifndef _CM_ERROR_H
#define _CM_ERROR_H
#ifdef __cplusplus
extern "C" {
#endif

enum cm_error {
	CM_ERR_NOTIMPL		= -256,
	CM_ERR_MISSING		= -257,
	CM_ERR_NOUSR 		= -258,
	CM_ERR_NOGRP 		= -259,
	CM_ERR_NOTFILE		= -260,
	CM_ERR_NOTDIR		= -261,
	CM_ERR_NOTLINK		= -262,
	CM_ERR_NOTRGT		= -263,
	CM_ERR_GIDEXISTS	= -264,
	CM_ERR_UIDEXISTS	= -265,
	CM_ERR_NOPKG		= -266,
};

char *cm_strerror(int e);

#ifdef __cplusplus
}
#endif
#endif
