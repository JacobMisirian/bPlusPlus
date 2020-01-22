#ifndef _TOKEN_H_

#include <stdlib.h>
#include <string.h>

typedef enum {
  ASSIGN_TOK, CBRACE_TOK, COLON_TOK,  COMMA_TOK, COMP_TOK,   CPAREN_TOK,  CSQUARE_TOK,   DOT_TOK,
  ID_TOK,     INT_TOK,    OBRACE_TOK, OP_TOK,    OPAREN_TOK, OSQUARE_TOK, SEMICOLON_TOK, STRING_TOK
} token_type_t;

struct token {
  token_type_t type;
  char       * val;
};

struct token * token_init (token_type_t   type, char * val, int size);
void           token_free (struct token * token);

#define _TOKEN_H_

#endif
