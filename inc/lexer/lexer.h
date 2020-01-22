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

struct lexer * lexer_init (char         * file_path);
void           lexer_free (struct lexer * lexer);

void lexer_scan (struct lexer * lexer);

#endif
