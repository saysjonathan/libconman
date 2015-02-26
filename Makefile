PREFIX		= /usr/local
VERSION		= 0.1.0
VERMAJ		= 0
INCS		= -I. -I/usr/include -I./include
CFLAGS		= -g -std=c99 -pedantic -Wall ${INCS} -D_DEFAULT_SOURCE
CFLAGS_SH 	= ${CFLAGS} -fPIC -DSHARED
CFLAGS_ST	= ${CFLAGS}
SRCS		= $(wildcard src/**/*.c)
OBJS		= ${SRCS:.c=.o}
LOBJS		= ${SRCS:.c=.lo}
SHLIB		= lib/libconman.so
STLIB		= lib/libconman.a
VERLIB		= lib/libconman.so.${VERSION}
INC		= $(wildcard include/conman/*.h)

all: pre ${VERLIB} ${STLIB}

pre:
	@echo creating build directories
	@mkdir -p lib

clean:
	@echo cleaning
	@rm -f ${OBJS}
	@rm -f ${LOBJS}
	@rm -rf lib

%.o: %.c
	cc ${CFLAGS_ST} -c -o $@ $<

%.lo: %.c
	cc ${CFLAGS_SH} -c -o $@ $<

${STLIB}: ${OBJS}
	@ar rc $@ ${OBJS}
	@ranlib $@

${VERLIB}: ${LOBJS}
	cc ${CFLAGS_SH} -shared -Wl,-soname,${SHLIB}.${VERMAJOR} -o $@ ${LOBJS}

install: all
	@install -d ${PREFIX}/include/conman
	@install -D -m 644 ${INC} ${PREFIX}/include/conman
	@install -d ${PREFIX}/lib
	@install -D -m 755 ${VERLIB} ${PREFIX}/lib
	@ln -sf ${PREFIX}/${VERLIB} ${PREFIX}/${SHLIB}

uninstall:
	@rm -f ${PREFIX}/${STLIB}
	@rm -f ${PREFIX}/${SHLIB}
	@rm -f ${PREFIX}/${VERLIB}
	@rm -rf ${PREFIX}/include/conman

.PHONY: all pre clean install uninstall
