#include <token.h>

struct token * token_init (token_type_t type, char * val, int size) {
  struct token * token;

  token = calloc (1, sizeof (struct token));

  token->type = type;
  if (size > 0) {
    token->val = calloc (size + 1, sizeof (char));
    memcpy (token->val, val, size);
    token->val [size] = 0;
  } else {
    token->val = 0;
  }

  return token;
}

void token_free (struct token * token) {
  if (token->val) {
    free (token->val);
  }

  free (token);
}
