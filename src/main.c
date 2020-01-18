#include <lexer/lexer.h>
#include <util/vector.h>

int main (int argc, char * argv []) {
  struct vector * tokens;
  struct lexer  * lexer;

  lexer = init_lexer ("printf (\"Hello, World\");");
  lexer_scan (lexer);

  tokens = lexer->tokens;

  for (int i = 0; i < tokens->count; i++) {
    printf ("%d \"%s\"\n", ((struct token *)vector_get (tokens, i))->type, ((struct token *)vector_get (tokens, i))->val);
  }
}
