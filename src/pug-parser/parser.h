
#ifndef __PUG_PARSER_H__
#define __PUG_PARSER_H__

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <pug/base.h>

// workaround for peg/leg/greg's shady parsing of "{}" even in
// character class literals
#define _OBRACK '{'
#define _CBRACK '}'
#define _OSBRACK "{"
#define _CSBRACK "}"

#define YY_ALLOC(N, D)      pug_malloc(N)
#define YY_CALLOC(N, S, D)  pug_malloc((N) * (S))
#define YY_REALLOC(B, N, D) pug_realloc(B, N)
#define YY_FREE             pug_free

void pug_parser_error(void *this, int code, bstring message, int pos);

// token opsition macros
#define tokenPos { core->token[0] = thunk->begin + G->offset; core->token[1] = (thunk->end - thunk->begin); }
#define tokenPosPlusOne { core->token[0] = thunk->begin + G->offset + 1; core->token[1] = (thunk->end - thunk->begin); }

#define rewindWhiteSpace { \
    /* only rewind if at end of file */ \
    if (core->eof == 1) { \
      int originalPos = G->pos; \
      bstring c = G->buf + G->pos; \
      /* rewind until we reach something non-whitespace */ \
      while (G->pos > 0) { \
        c--; G->pos--; \
        char cc = *c; \
        if (!((cc) == ' ' || (cc) == '\t' || (cc) == '\n' || (cc) == '\r')) break; \
      } \
    } \
}

/////////////////////                 error IDs start                ////////////////////////

// PPE stands for 'pug parser error'

enum pug_parser_error_t {
    PPE_EXP_TOPLEVEL = 1,
    PPE_EXP_ARG,
    PPE_EXP_STAT,
    PPE_MISSING_OPERAND,
};

/////////////////////                  error IDs end                 ////////////////////////

// Throw error at current parsing pos. Used when nothing valid matches.
#define throwError(code, message) \
    pug_parser_error(core->this, (code), (message), G->pos + G->offset)

// Throw error at last matched token pos. Used with invalid tokens being
// parsed for more helpful messages (e.g. misplaced suffixes).
#define throwTokenError(code, message) \
    pug_parser_error(core->this, (code), (message), core->token[0])

#define missingOp(c) { \
    rewindWhiteSpace; \
    bstring message = bformat("Missing right operand for '%s' operator!", (c)); \
    throwError(PPE_MISSING_OPERAND, message); \
}

#define YYSTYPE void*

// the default is 1024, but it causes buffers to be reallocated 4 or 5
// times during the parsing. This is a better default for us, only a few
// modules need to reallocate with that setting
#define YY_BUFFER_START_SIZE 16384

// in old peg/leg versions, this was set to 32, but it's wayyy too small
// for a non-trivial grammar like ooc's
#define YY_STACK_SIZE YY_BUFFER_START_SIZE

// Uncomment for *very* verbose output from greg
//#define YY_DEBUG

///////////////////// re-entrant data structures ////////////////////////

typedef int (*_pug_parser_io_read)(void *, size_t, void *);
struct _pug_parser_io {
    _pug_parser_io_read read;
};

typedef struct _pug_parser_core {
    /* The user's data */
    void *this;
    /* Current line number */
    int yylineno;
    /* Path of the file we're parsing. */
    bstring path;
    /* The stream we're reading from. */
    void *stream;
    /* Length of the stream (only used for memory streams) */
    size_t streamlen;
    /* Offset in the stream (only used for memory streams) */
    size_t streamoffset;
    /* our IO interface */
    struct _pug_parser_io io;
    /* The begin position and length of the current token in the text */
    int token[2];
    /* type parsing buffer */
    char typeBuffer[4096];
    /* 0 if still reading file, 1 if eof */
    int eof;
} pug_parser_core;

#define YY_XTYPE pug_parser_core *
#define YY_XVAR core

void pug_parser_yyinput(char *buf, int *result, int max_size, pug_parser_core *core);
#define YY_INPUT(buf, result, max_size, core) pug_parser_yyinput(buf, &result, max_size, core)

////////////////////// interface //////////////////////

int pug_parser_parse(void *this, bstring path);

////////////////////// callbacks //////////////////////

void pug_parser_set_token_position_pointer(void *, int *, int *);
void* pug_parser_strdup(void *);
void* pug_parser_on_operation(void *, char, int, int);
void* pug_parser_on_function_start(void *, bstring name);
void* pug_parser_on_argument(void *, bstring name);
void* pug_parser_on_function_end(void *);

#endif // __PUG_PARSER_H__

