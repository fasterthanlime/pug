
#include "parser.h"
#include <stdlib.h>

int main() {
    pug_parser_context_t *ctx = pug_parser_create(NULL);
    while (pug_parser_parse(ctx, NULL));
    pug_parser_destroy(ctx);
    return 0;
}
