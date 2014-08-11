
#include "function.h"

IMPLEMENT_VECTOR_TYPE ( pug_argument, pug_argument_t )
IMPLEMENT_VECTOR_TYPE ( pug_function, pug_function_t )

void pug_function_init(pug_function_t *f) {
    vector_pug_argument_create(&f->args, 1);
}
