
.PHONY: all prepare clean

DEPSPREFIX:=${CURDIR}/prefix

LIBCOLLECTIONS_H:=prefix/include/libcollections/libcollections-config.h
LIBJIT_H:=prefix/include/jit/jit.h

all: prepare libcollections libjit
	@echo "Deps all set!"

clean:
	rm -rf ${DEPSPREFIX} build
	
prepare:
	@mkdir -p ${DEPSPREFIX} ${DEPSPREFIX}/bin ${DEPSPREFIX}/lib

# basic macro-based C data structures (array, vector, hashtables, string wrappers, etc.)

libcollections: ${LIBCOLLECTIONS_H}

${LIBCOLLECTIONS_H}:
	mkdir -p build/libcollections
	cd build/libcollections && ${CURDIR}/libcollections/configure --prefix=${DEPSPREFIX}
	${MAKE} -C build/libcollections install

# GNU'd just-in-time compiler, portable, fast?

libjit: ${LIBJIT_H}

${LIBJIT_H}:
	mkdir -p build
	rm -rf build/libjit
	cp -rf ${CURDIR}/libjit build/libjit
	cd build/libjit && ./configure --prefix=${DEPSPREFIX}
	${MAKE} -C build/libjit install
