#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "common.h"

int cm_run_cmd(char *path, char * const args[], int (*fn)(const char *)) {
        char buf[2048];
        size_t bs = sizeof(buf);
	pid_t p;
	int pfd[2], i, s;
	FILE *f;

	errno = 0;
	if((i = pipe(pfd)) != 0) {
		return -errno;
	}
	p = fork();
	if(p == 0) {
		close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		dup2(pfd[1], STDERR_FILENO);
		execv(path, args);
	}

	close(pfd[1]);
	if((f = fdopen(pfd[0], "r")) == NULL) {
		return -errno;
	}
	waitpid(p, &s, 0);
	if(fn != NULL) {
		while(fgets(buf, bs, f) != NULL) {
			if(fn(buf) != 0) {
				break;
			}
		}
	}
	close(pfd[0]);
	fclose(f);
	if(WIFEXITED(s)) {
		return WEXITSTATUS(s);
	}
	return 0;
}
