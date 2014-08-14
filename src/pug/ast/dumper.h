
#pragma once

#ifndef __PUG_AST_DUMPER_H__
#define __PUG_AST_DUMPER_H__

#include <jansson.h>
#include "module.h"

int pug_module_dump_file(pug_module_t *module, char *path);

json_t *pug_module_dump(pug_module_t *module);

#endif // __PUG_AST_DUMPER_H__

