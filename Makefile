PREFIX 	= /usr/local
SRCS	= $(wildcard src/**/*.c)
LOBJS	= ${SRCS:.c=.lo}
SHLIB	= lib/libconman.so
INC	= $(wildcard include/conman/*.h)

all: pre ${SHLIB}

pre:
	@echo creating build directories
	@mkdir -p lib

clean:
	@echo cleaning
	@rm -f ${LOBJS}
	@rm -rf lib

%.lo: %.c
	cc -g -std=c11 -pedantic -Wall -O0 -I. -I/usr/include -I./include -fPIC -DSHARED -D_DEFAULT_SOURCE -c -o $@ $<

${SHLIB}: ${LOBJS}
	cc -std=c11 -pedantic -Wall -O0 -I. -I/usr/include -I./include -fPIC -DSHARED -D_DEFAULT_SOURCE -shared -o $@ ${LOBJS}

install:
	@install -d ${PREFIX}/include/conman
	@install -D -m 644 ${INC} ${PREFIX}/include/conman
	@install -d ${PREFIX}/lib
	@install -D -m 755 ${SHLIB} ${PREFIX}/lib

uninstall:
	@rm -f ${PREFIX}/${SHLIB}
	@rm -rf ${PREFIX}/include/conman

.PHONY: all pre clean install uninstall
