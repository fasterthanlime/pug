
# packcc doesn't come with a makefile, so we make do.

ifndef DEVPREFIX
  $(error "Please set the DEVPREFIX environment variable")
endif

.PHONY: clean

${DEVPREFIX}/packcc: packcc.c
	${CC} packcc.c -o ${DEVPREFIX}/bin/packcc

clean:
	rm -f ${DEVPREFIX}/packcc
