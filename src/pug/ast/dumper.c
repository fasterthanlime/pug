
#include "dumper.h"

int pug_module_dump_file(pug_module_t *module, char *path) {
  json_t *root = pug_module_dump(module);
  size_t flags = 0;
  return json_dump_file(root, path, flags);
}

json_t *pug_module_dump(pug_module_t *module) {
  json_t *root = json_pack("{}");
  json_object_set(root, "name", json_string(module->name));
  return root;
}

