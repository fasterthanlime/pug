
#pragma once

#ifndef __PUG_BASE__H__
#define __PUG_BASE__H__

#include <stdlib.h>
#include <stdio.h>

#include <libcollections/vector.h>
#include <libcollections/dlist.h>

#include <gc.h>

// GC-powered memory allocation
#define pug_malloc(N)      GC_malloc(N)
#define pug_calloc(N, S)   GC_malloc((N) * (S))
#define pug_realloc(B, N)  GC_realloc(B, N)
#define pug_free           GC_free

// logging & stuff
int pug_bail(char *fmt, ...);

#endif // __PUG_BASE__H__
