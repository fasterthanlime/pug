
#pragma once

#ifndef __PUG_AST_FUNCTION_H__
#define __PUG_AST_FUNCTION_H__

#include <libcollections/vector.h>
#include <pug/base.h>

typedef struct pug_argument {
  bstring name;
} pug_argument_t;

DECLARE_VECTOR_TYPE   ( pug_argument, pug_argument_t )

void pug_argument_init(pug_argument_t *f);

typedef struct pug_function {
  bstring name;
  vector_pug_argument_t args;
} pug_function_t;

DECLARE_VECTOR_TYPE   ( pug_function, pug_function_t )

void pug_function_init(pug_function_t *f);

#endif // __PUG_AST_FUNCTION_H__

