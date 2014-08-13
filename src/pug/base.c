

#include "base.h"
#include <stdarg.h>
#include <stdio.h>

int pug_bail(char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  int ret = vprintf(fmt, args);
  va_end(args);

  exit(1);
  return ret;
}

