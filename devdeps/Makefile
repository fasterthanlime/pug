
.PHONY: all prepare packcc

DEVPREFIX:=${CURDIR}/prefix
export DEVPREFIX

.PHONY: prepare clean

all: prepare packcc
	
prepare:
	@mkdir -p ${DEVPREFIX} ${DEVPREFIX}/bin ${DEVPREFIX}/lib

clean:
	@${MAKE} -C packcc clean


packcc:
	@${MAKE} -C packcc
