
PACKCC?=packcc
CC:=clang

# Hi!
.PHONY: all devdeps deps

all: pug
	@echo "Phew."
	
pug: grammar source/pug.c
	mkdir -p bin
	${CC} source/pug.c -o bin/pug
	
grammar: source/parser.c

source/parser.c: grammar/pug.leg
	cd source && ${PACKCC} -o parser ${CURDIR}/grammar/pug.leg

devdeps:
	${MAKE} -C devdeps

deps:
	${MAKE} -C deps
