include mk/os.mk
PREFIX 	 = /usr/local
INCS	 = -I. -I/usr/include -I./include
CFLAGS 	 = -std=c99 -pedantic -Wall -O0 -fPIC -DSHARED -D_DEFAULT_SOURCE -D_BSD_SOURCE -D_POSIX_SOURCE
ALLSRCS	 = $(wildcard src/**/*.c)
PKGSRCS  = $(wildcard src/**/${PKGMGR}/*.c)
SRCS	 = ${ALLSRCS} ${PKGSRCS}
LOBJS	 = ${SRCS:.c=.lo}
SHLIB	 = lib/libconman.so
INC	 = $(wildcard include/*.h)
INCO	 = $(wildcard include/**/*.h)

all: pre ${SHLIB}

pre:
	@echo creating build directories
	@mkdir -p lib
	@echo ${INC}

clean:
	@echo cleaning
	@rm -f ${LOBJS}
	@rm -rf lib

%.lo: %.c
	cc ${CFLAGS} ${INCS} -c -o $@ $<

${SHLIB}: ${LOBJS}
	cc ${CFLAGS} ${INCS} -shared -o $@ ${LOBJS}

install: all
	@install -d ${PREFIX}/include/conman
	@install -D -m 644 ${INC} ${PREFIX}/include
	@install -D -m 644 ${INCO} ${PREFIX}/include/conman
	@install -d ${PREFIX}/lib
	@install -D -m 755 ${SHLIB} ${PREFIX}/lib

uninstall:
	@rm -f ${PREFIX}/${SHLIB}
	@rm -rf ${PREFIX}/include/conman
	@rm -rf ${PREFIX}/${INC}

.PHONY: all pre clean install uninstall
