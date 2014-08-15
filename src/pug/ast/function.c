
#include "function.h"

IMPLEMENT_VECTOR_TYPE ( pug_argument, pug_argument_t )

void pug_argument_init(pug_argument_t *f) {
  return;
}

IMPLEMENT_VECTOR_TYPE ( pug_function, pug_function_t )

void pug_function_init(pug_function_t *f) {
  vector_pug_argument_create(&f->arguments, 1);
}
