#include "conman/state.h"
#include "conman/util.h"

int diff_absent(int state) {
	int i = 1;
	switch(state) {
		case CM_ABSENT:
			i = 0;
			break;
	}
	return i;
}

int diff_present(int state) {
	int i = 1;
	switch(state) {
		case CM_PRESENT:
			i = 0;
			break;
		case CM_LATEST:
			i = 0;
			break;
		case CM_OUTDATED:
			i = 0;
			break;
	}
	return i;
}

int diff_outdated(int state) {
	int i = 1;
	switch(state) {
		case CM_PRESENT:
			i = 0;
			break;
	}
	return i;
}

int diff_latest(int state) {
	int i = 1;
	switch(state) {
		case CM_LATEST:
			i = 0;
			break;
	}
	return i;
}

int cm_diff_state(int actual, int desired) {
	int i;
	switch(actual) {
		case CM_ABSENT:
			i = diff_absent(desired);
			break;
		case CM_PRESENT:
			i = diff_present(desired);
			break;
		case CM_OUTDATED:
			i = diff_outdated(desired);
			break;
		case CM_LATEST:
			i = diff_latest(desired);
			break;
	}
	return i;
}
