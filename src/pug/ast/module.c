
#include "module.h"

IMPLEMENT_VECTOR_TYPE ( pug_module, pug_module_t )

void pug_module_init(pug_module_t *m) {
    vector_pug_function_create(&m->functions, 1);
}
