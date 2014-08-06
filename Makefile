
# Hi!
.PHONY: all devdeps deps

all:
	@echo "Time to read the Makefile!"

devdeps:
	${MAKE} -C devdeps

deps:
	${MAKE} -C deps
