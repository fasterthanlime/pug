
#pragma once

#ifndef __PUG_AST_MODULE_H__
#define __PUG_AST_MODULE_H__

#include <libcollections/vector.h>
#include <pug/base.h>
#include "function.h"

typedef struct pug_module {
  bstring name;
  vector_pug_function_t functions;
} pug_module_t;

DECLARE_VECTOR_TYPE   ( pug_module, pug_module_t )

void pug_module_init(pug_module_t *module, bstring name);

#endif // __PUG_AST_MODULE_H__

