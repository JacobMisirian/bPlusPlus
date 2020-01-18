#ifndef _TOKEN_H_

#include <stdlib.h>
#include <string.h>

typedef enum {
  TOK_ASSIGN, TOK_CBRACE, TOK_COLON, TOK_COMMA, TOK_COMP, TOK_CPAREN, TOK_CSQUARE, TOK_DOT, TOK_IDENTIFIER,
  TOK_INTEGER, TOK_OBRACE, TOK_OP, TOK_OPAREN, TOK_OSQUARE, TOK_SEMICOLON, TOK_STRING
} token_type_t;

struct token {
  token_type_t type;
  char       * val;
};

struct token * init_token (token_type_t   type, char * val, int size);
void           free_token (struct token * token);

#define _TOKEN_H_

#endif
