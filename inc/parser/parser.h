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

struct parser * init_parser (struct vector * tokens);
void            free_parser (struct parser * parser);

struct ast_node * parse ();

#endif
