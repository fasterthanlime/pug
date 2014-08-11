
#include "pug.h"

typedef struct pug_parser_state {
    pug_module_t *module;
} pug_parser_state_t;

static pug_parser_state_t parser_state;

void pug_parser_state_init(pug_parser_state_t *state) {
  state->module = malloc(sizeof(pug_module_t));
}

int main() {
    pug_parser_state_init(&parser_state);
    pug_module_init(parser_state.module);

    pug_parser_context_t *ctx = pug_parser_create(NULL);
    pug_parser_parse(ctx, NULL);
    pug_parser_destroy(ctx);

    printf("Replaying...\n");
    for (int i = 0; i < vector_pug_function_size(&parser_state.module->functions); i++) {
        pug_function_t *function = vector_pug_function_get(&parser_state.module->functions, i);
        printf("Had function %s\n", function->name);
    }

    return 0;
}

void* pug_parser_on_operation(char op, int lhs, int rhs) {
    pug_operation_t *operation = malloc(sizeof(pug_operation_t));
    *operation = (pug_operation_t) { op, lhs, rhs };
    //vector_pug_operation_push(&collection, operation);
    return operation;
}

void *pug_parser_on_function_start(char *name) {
    pug_function_t *function = malloc(sizeof(pug_function_t));
    pug_function_init(function);
    function->name = name;
    return NULL;
}

void *pug_parser_on_function_end(pug_function_t *function) {
    vector_pug_function_push(&parser_state.module->functions, function);
}

