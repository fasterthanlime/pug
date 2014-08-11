
#pragma once

#ifndef __PUG_AST_OPERATION_H__
#define __PUG_AST_OPERATION_H__

#include <libcollections/vector.h>

typedef struct operation {
  char op;
  int lhs;
  int rhs;
} operation_t;

DECLARE_VECTOR_TYPE   ( operation, operation_t )
IMPLEMENT_VECTOR_TYPE ( operation, operation_t )

#endif // __PUG_AST_OPERATION_H__
