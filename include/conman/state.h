#ifndef _CM_STATE_H
#define _CM_STATE_H
#ifdef __cplusplus
extern "C" {
#endif

enum cm_state {
	CM_ABSENT,
	CM_PRESENT,
	CM_OUTDATED,
	CM_LATEST
};

#ifdef __cplusplus
}
#endif
#endif
