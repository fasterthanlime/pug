
#include "pug.h"

typedef struct pug_parser_state {
  bstring path;
  pug_module_t *module;
  struct lc_dlist stack; 
} pug_parser_state_t;

static int* global_token_p;
static int* global_lineno_p;

void pug_noop(void) {
  return;
}

void pug_parser_state_init(pug_parser_state_t *state, bstring path) {
  state->path = path;
  state->module = pug_malloc(sizeof(pug_module_t));
  dlist_create(&state->stack, (void*) pug_noop, pug_malloc, pug_free);

  int index = bstrrchr(path, '/');
  bstring name = bmidstr(path, index + 1, blength(path) - 3 - index - 1);
  pug_module_init(state->module, name);
}

int main(int argc, char **argv) {
  pug_init();

  if (argc < 2) {
    pug_bail("Usage: %s FILE.pg\n", argv[0]);
  }

  pug_parser_state_t *state = pug_malloc(sizeof(pug_parser_state_t));
  pug_parser_state_init(state, bfromcstr(argv[1]));

  pug_parser_parse(state, state->path);

  // dump the module
  bstring dumppath = bstrcpy(state->module->name);
  bconcat(dumppath, bfromcstr(".json"));

  printf("Dumping to %s\n", bdata(dumppath));
  pug_module_dump_file(state->module, dumppath);

  return 0;
}

void* pug_parser_on_operation(void *this, char op, int lhs, int rhs) {
  pug_parser_state_t *state = this;
  pug_operation_t *operation = pug_malloc(sizeof(pug_operation_t));
  *operation = (pug_operation_t) { op, lhs, rhs };
  return operation;
}

void *pug_parser_on_function_start(void *this, bstring name) {
  pug_parser_state_t *state = this;
  pug_function_t *function = pug_malloc(sizeof(pug_function_t));
  pug_function_init(function);
  function->name = name;
  dlist_insert_front(&state->stack, function);
  return function;
}

void *pug_parser_on_argument(void *this, bstring name) {
  pug_parser_state_t *state = this;
  pug_function_t *function = state->stack.head->data;
  pug_argument_t *arg = pug_malloc(sizeof(pug_argument_t));
  pug_argument_init(arg);
  arg->name = name;
  vector_pug_argument_push(&function->arguments, arg);
  return arg;
}

void *pug_parser_on_function_end(void *this) {
  pug_parser_state_t *state = this;
  pug_function_t *function = state->stack.head->data;
  dlist_remove_front(&state->stack);
  vector_pug_function_push(&state->module->functions, function);
  return function;
}

void pug_parser_set_token_position_pointer(void *this, int *token_p, int *lineno_p) {
  global_token_p = token_p;
  global_lineno_p = lineno_p;
  return;
}

void pug_parser_error(void *this, int code, bstring message, int pos) {
  struct pug_parser_state *state = this;
  pug_bail("%s:%d %s\n", state->path, pos, message);
}

