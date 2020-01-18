#ifndef _LEXER_H_
#define _LEXER_H_

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <token.h>
#include <util/vector.h>

struct lexer {
  char          * source;
  int             pos;
  int             len;
  struct vector * tokens;
};

struct lexer * init_lexer (char         * file_path);
void           free_lexer (struct lexer * lexer);

void lexer_scan (struct lexer * lexer);

#endif
