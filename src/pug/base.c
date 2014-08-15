

#include "base.h"
#include <stdarg.h>
#include <stdio.h>

int pug_init() {
  GC_INIT();
  json_set_alloc_funcs(GC_malloc, GC_free);
  return 0;
}

int pug_bail(char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  int ret = vprintf(fmt, args);
  va_end(args);

  exit(1);
  return ret;
}

