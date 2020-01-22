#ifndef _PARSER_H_
#define _PARSER_H_

#include <parser/ast_node.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>
#include <util/string.h>
#include <util/vector.h>

struct parser {
  struct vector * tokens;
  int             pos;
  int             len;
};

struct parser * parser_init (struct vector * tokens);
void            parser_free (struct parser * parser);

struct ast_node * parse ();

#endif
