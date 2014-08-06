
.PHONY: all prepare libcollections

PREFIX:=${CURDIR}/prefix
export PREFIX

all: prepare libcollections
	
prepare:
	@mkdir -p ${PREFIX} ${PREFIX}/bin ${PREFIX}/lib

libcollections: prefix/include/libcollections/libcollections-config.h

prefix/include/libcollections/libcollections-config.h:
	mkdir -p build/libcollections
	cd build/libcollections && ${CURDIR}/libcollections/configure --prefix=${PREFIX}
	${MAKE} -C build/libcollections install
