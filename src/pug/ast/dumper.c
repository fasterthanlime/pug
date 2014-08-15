
#include "dumper.h"

int pug_module_dump_file(pug_module_t *module, bstring path) {
  json_t *root = pug_module_dump(module);
  size_t flags = JSON_INDENT(2);
  return json_dump_file(root, bdata(path), flags);
}

json_t *pug_module_dump(pug_module_t *module) {
  json_t *jmodule = json_object();
  json_object_set(jmodule, "name", json_bstring(module->name));

  json_t *jfunctions = json_array();
  for (int i = 0; i < vector_pug_function_size(&module->functions); i++) {
    pug_function_t *function = vector_pug_function_get(&module->functions, i);
    json_t *jfunction = pug_function_dump(function);
    json_array_append(jfunctions, jfunction);
  }
  json_object_set(jmodule, "functions", jfunctions);

  return jmodule;
}

json_t *pug_function_dump(pug_function_t *function) {
  json_t *jfunction = json_object();
  json_object_set(jfunction, "name", json_bstring(function->name));

  json_t *jarguments = json_array();
  for (int i = 0; i < vector_pug_argument_size(&function->arguments); i++) {
    pug_argument_t *argument = vector_pug_argument_get(&function->arguments, i);
    json_t *jargument = json_object();
    json_object_set(jargument, "name", json_bstring(argument->name));
    json_array_append(jarguments, jargument);
  }
  json_object_set(jfunction, "arguments", jarguments);
  return jfunction;
}

