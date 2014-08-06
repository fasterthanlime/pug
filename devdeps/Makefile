
.PHONY: all prepare packcc

DEVPREFIX:=${CURDIR}/prefix
export DEVPREFIX

all: prepare packcc
	
prepare:
	@mkdir -p ${DEVPREFIX} ${DEVPREFIX}/bin ${DEVPREFIX}/lib

packcc:
	${MAKE} -C packcc
