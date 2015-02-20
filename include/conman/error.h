#ifndef _CM_ERROR_H
#define _CM_ERROR_H
#ifdef __cplusplus
extern "C" {
#endif

enum cm_error {
	CM_ERR_NOUSR 	= -256,
	CM_ERR_NOGRP 	= -257,
	CM_ERR_NOTFILE	= -258,
	CM_ERR_NOTDIR	= -259,
	CM_ERR_NOTLINK	= -260,
	CM_ERR_NOTRGT	= -261,
};

char *cm_strerror(int e);

#ifdef __cplusplus
}
#endif
#endif
