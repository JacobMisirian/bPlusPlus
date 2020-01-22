#include <emit/scope.h>

struct scope * scope_init () {
  struct scope * scope;

  scope = calloc (1, sizeof (struct scope));

  scope->ids    = calloc (SCOPE_SIZE, sizeof (char *));
  scope->vals   = calloc (SCOPE_SIZE, sizeof (int));
  scope->length = 0;
  scope->size   = SCOPE_SIZE;

  return scope;
}

void scope_free (struct scope * scope) {
  free (scope->ids);
  free (scope->vals);
  free(scope);
}

static int  scope_get_index (struct scope * scope, char * id);
static void reallocate      (struct scope * scope);

int scope_get (struct scope * scope, char * id) {
  int index;

  index = scope_get_index (scope, id);
  if (index == -1) { return -1; }
  else             { return scope->vals [index]; }
}

void scope_set (struct scope * scope, char * id, int val) {
  reallocate (scope);

  scope->ids  [scope->length] = id;
  scope->vals [scope->length] = val;

  scope->length ++;
}

static int scope_get_index (struct scope * scope, char * id) {
  for (int i = 0; i < scope->length; i++) {
    if (strcmp (scope->ids [i], id) == 0) {
      return i;
    }
  }

  return -1;
}

static void reallocate (struct scope * scope) {
  while (scope->length >= scope->size) {
    scope->size += SCOPE_SIZE;
    scope->ids   = realloc (scope->ids,  scope->size * sizeof (char *));
    scope->vals  = realloc (scope->vals, scope->size * sizeof (int));
  }
}
