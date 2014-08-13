
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

int main(int argc, char **argv) {
  if (argc < 2) {
    pug_bail("Usage: %s FILE.pg\n", argv[0]);
  }

  pug_parser_state_t *state = pug_malloc(sizeof(pug_parser_state_t));
  pug_parser_state_init(state);

  pug_parser_parse(state, argv[1]);

  printf("Replaying...\n");
  for (int i = 0; i < vector_pug_function_size(&state->module->functions); i++) {
    pug_function_t *function = vector_pug_function_get(&state->module->functions, i);
    printf("Had function %s", function->name);
    bool first = true;
    int num_args = vector_pug_argument_size(&function->args);

    if (num_args > 0) {
      printf("(");
      for (int j = 0; j < num_args; j++) {
        pug_argument_t *arg = vector_pug_argument_get(&function->args, j);
        if (first) {
          first = false;
        } else {
          printf(", ");
        }
        printf("%s", arg->name);
      }
      printf(")");
    }
    printf("%s", "\n");
  }

  return 0;
}

void* pug_parser_strdup(void *str) {
  return strdup(str);
}

void* pug_parser_on_operation(void *this, char op, int lhs, int rhs) {
  pug_parser_state_t *state = this;
  pug_operation_t *operation = malloc(sizeof(pug_operation_t));
  *operation = (pug_operation_t) { op, lhs, rhs };
  return operation;
}

void *pug_parser_on_function_start(void *this, char *name) {
  pug_parser_state_t *state = this;
  pug_function_t *function = malloc(sizeof(pug_function_t));
  pug_function_init(function);
  function->name = name;
  dlist_insert_front(&state->stack, function);
  return function;
}

void *pug_parser_on_argument(void *this, char *name) {
  pug_parser_state_t *state = this;
  pug_function_t *function = state->stack.head->data;
  pug_argument_t *arg = malloc(sizeof(pug_argument_t));
  pug_argument_init(arg);
  arg->name = name;
  vector_pug_argument_push(&function->args, arg);
  return arg;
}

void *pug_parser_on_function_end(void *this) {
  pug_parser_state_t *state = this;
  pug_function_t *function = state->stack.head->data;
  dlist_remove_front(&state->stack);
  vector_pug_function_push(&state->module->functions, function);
  return function;
}

void pug_parser_set_token_position_pointer(void *this, int *p_token, int *p_lineno) {
  printf("Got token pos: %d, %d, lineno: %d\n", p_token[0], p_token[1], p_lineno[0]);
  return;
}

