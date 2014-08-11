
#include "pug.h"

static vector_pug_operation_t collection;

int main() {
  vector_pug_operation_create(&collection, 1);

  pug_parser_context_t *ctx = pug_parser_create(NULL);
  pug_parser_parse(ctx, NULL);
  pug_parser_destroy(ctx);

  printf("Replaying...\n");
  for (int i = 0; i < vector_pug_operation_size(&collection); i++) {
    pug_operation_t *operation = vector_pug_operation_get(&collection, i);
    printf("Computed %d %c %d\n", operation->lhs, operation->op, operation->rhs);
  }

  return 0;
}

void pug_parser_on_operation(char op, int lhs, int rhs) {
  struct pug_operation operation = { op, lhs, rhs };
  vector_pug_operation_push(&collection, &operation);
}

