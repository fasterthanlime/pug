
#include "pug.h"

typedef struct pug_parser_state {
  pug_module_t *module;
  struct lc_dlist stack; 
} pug_parser_state_t;

void pug_noop(void) {
  return;
}

void pug_parser_state_init(pug_parser_state_t *state) {
  state->module = malloc(sizeof(pug_module_t));
  dlist_create(&state->stack, (void*) pug_noop, malloc, free);
  pug_module_init(state->module);
}

int main() {
  pug_parser_state_t *state = malloc(sizeof(pug_parser_state_t));
  pug_parser_state_init(state);

  pug_parser_context_t *ctx = pug_parser_create(state);
  pug_parser_parse(ctx, NULL);
  pug_parser_destroy(ctx);

  printf("Replaying...\n");
  for (int i = 0; i < vector_pug_function_size(&state->module->functions); i++) {
    pug_function_t *function = vector_pug_function_get(&state->module->functions, i);
    printf("Had function %s\n", function->name);
  }

  return 0;
}

void* pug_parser_strdup(void *str) {
  return strdup(str);
}

void* pug_parser_on_operation(void *auxil, char op, int lhs, int rhs) {
  pug_parser_state_t *state = auxil;
  pug_operation_t *operation = malloc(sizeof(pug_operation_t));
  *operation = (pug_operation_t) { op, lhs, rhs };
  return operation;
}

void *pug_parser_on_function_start(void *auxil, char *name) {
  pug_parser_state_t *state = auxil;
  pug_function_t *function = malloc(sizeof(pug_function_t));
  pug_function_init(function);
  function->name = name;
  dlist_insert_front(&state->stack, function);
  return function;
}

void *pug_parser_on_function_end(void *auxil) {
  pug_parser_state_t *state = auxil;
  // pop stuff from queue
  pug_function_t *function = state->stack.head->data;
  dlist_remove_front(&state->stack);
  vector_pug_function_push(&state->module->functions, function);
}

