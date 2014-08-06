
.PHONY: all prepare libcollections

PREFIX:=${CURDIR}/prefix
export PREFIX

all: prepare libcollections
	
prepare:
	mkdir -p ${PREFIX}
	mkdir -p ${PREFIX}/bin
	mkdir -p ${PREFIX}/lib

libcollections:
	mkdir -p build/libcollections
	cd build/libcollections && ${CURDIR}/libcollections/configure --prefix=${PREFIX}
	${MAKE} -C build/libcollections install
