
#include "parser.h"
#include <libcollections/vector.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct operation {
  char op;
  int l;
  int r;
} operation_t;

DECLARE_VECTOR_TYPE   ( operation, operation_t )
IMPLEMENT_VECTOR_TYPE ( operation, operation_t )

static vector_operation_t collection;

int main() {
  vector_operation_create(&collection, 1);

  pug_parser_context_t *ctx = pug_parser_create(NULL);
  pug_parser_parse(ctx, NULL);
  pug_parser_destroy(ctx);

  printf("Replaying...\n");
  for (int i = 0; i < vector_operation_size(&collection); i++) {
    operation_t *operation = vector_operation_get(&collection, i);
    printf("Computed %d %c %d\n", operation->l, operation->op, operation->r);
  }

  return 0;
}

void pug_parser_on_operation(char op, int l, int r) {
  operation_t *operation = vector_operation_pushx(&collection);
  operation->op = op;
  operation->l = l;
  operation->r = r;
}

