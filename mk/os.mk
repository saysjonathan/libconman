uname := $(shell uname -s)
rhfile := $(shell test -f /etc/redhat-release; echo $$?)

ifeq ($(uname),Linux)
	ifeq ($(rhfile), 0)
		DIST = redhat
		PKGMGR = yum
	else
		DIST = other
		PKGMGR = other
	endif
endif
