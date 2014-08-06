/* A packrat parser generated by PackCC 1.2.0 */

#ifndef PCC_INCLUDED__PARSER_H
#define PCC_INCLUDED__PARSER_H

void pug_parser_on_operation(char, int, int);

#ifdef __cplusplus
extern "C" {
#endif

typedef struct pug_parser_context_tag pug_parser_context_t;

pug_parser_context_t *pug_parser_create(void *auxil);
int pug_parser_parse(pug_parser_context_t *ctx, int *ret);
void pug_parser_destroy(pug_parser_context_t *ctx);

#ifdef __cplusplus
}
#endif

#endif /* PCC_INCLUDED__PARSER_H */
