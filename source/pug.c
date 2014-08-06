
#include "parser.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
    pug_parser_context_t *ctx = pug_parser_create(NULL);
    while (pug_parser_parse(ctx, NULL));
    pug_parser_destroy(ctx);
    return 0;
}

void pug_parser_on_operation(char op, int l, int r) {
    printf("Computing %d %c %d\n", l, op, r);
}

