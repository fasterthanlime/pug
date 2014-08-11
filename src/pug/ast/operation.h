
#pragma once

#ifndef __PUG_AST_OPERATION_H__
#define __PUG_AST_OPERATION_H__

#include <libcollections/vector.h>

typedef struct pug_operation {
  char op;
  int lhs;
  int rhs;
} pug_operation_t;

DECLARE_VECTOR_TYPE   ( pug_operation, pug_operation_t )

#endif // __PUG_AST_OPERATION_H__
