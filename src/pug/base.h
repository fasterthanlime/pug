
#pragma once

#ifndef __PUG_BASE__H__
#define __PUG_BASE__H__

#include <stdlib.h>
#include <stdio.h>

#include <libcollections/vector.h>
#include <libcollections/dlist.h>

#include <gc.h>
#include <jansson.h>

// GC-powered memory allocation
#define pug_malloc       GC_malloc
#define pug_calloc(N, S) GC_malloc((N) * (S))
#define pug_realloc      GC_realloc
#define pug_free         GC_free

int pug_init();

// logging & stuff
int pug_bail(char *fmt, ...);

#endif // __PUG_BASE__H__
