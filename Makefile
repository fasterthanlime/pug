
PACKCC?=packcc
CC:=clang
CCFLAGS:=-Ideps/prefix/include -std=gnu99 -g -Os
LDFLAGS:=-Ldeps/prefix/lib -Wl,-rpath,${CURDIR}/deps/prefix/lib -lcollections

# Hi!
.PHONY: all devdeps deps

all: pug
	@echo "Phew."
	
pug: deps source/pug.c source/parser.c
	@mkdir -p bin
	${CC} ${CCFLAGS} source/pug.c source/parser.c ${LDFLAGS} -o bin/pug
	
grammar: source/parser.c

source/parser.c: grammar/pug.peg
	cd source && ${PACKCC} -o parser ${CURDIR}/grammar/pug.peg

devdeps:
	@${MAKE} -C devdeps

deps:
	@${MAKE} -C deps
