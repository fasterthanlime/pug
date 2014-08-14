
#include "module.h"

IMPLEMENT_VECTOR_TYPE ( pug_module, pug_module_t )

void pug_module_init(pug_module_t *module, char *name) {
  module->name = name;
  vector_pug_function_create(&module->functions, 1);
}

