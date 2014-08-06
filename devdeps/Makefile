
.PHONY: all prepare packcc

DEVPREFIX:=${CURDIR}/prefix
export DEVPREFIX

all: prepare packcc
	
prepare:
	mkdir -p ${DEVPREFIX}
	mkdir -p ${DEVPREFIX}/bin
	mkdir -p ${DEVPREFIX}/lib

packcc:
	${MAKE} -C packcc
