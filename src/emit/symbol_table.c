#include <emit/symbol_table.h>

struct symbol_table * symol_table_init () {
  struct symbol_table * table;

  table = calloc (1, sizeof (struct symbol_table));

  table->scopes = vector_init ();
  table->next   = 0;

  return table;
}

void symol_table_free (struct symbol_table * table) {
  for (int i = 0; i < table->scopes->count; i ++) {
    scope_free (vector_get (table->scopes, i));
  }
  vector_free (table->scopes);

  free        (table);
}

void enter_scope (struct symbol_table * table) {
  vector_push (table->scopes, scope_init ());
}

int get_symbol (struct symbol_table * table, char * id) {
  int val;

  for (int i = 0; i < table->scopes->count; i ++) {
    val = scope_get (vector_get (table->scopes, i), id);

    if (val != -1) {
      return val;
    }
  }

  return -1;
}

int handle_symbol (struct symbol_table * table, char * id) {
  if (!get_symbol (table, id)) {
    scope_set (vector_peek (table->scopes), id, table->next ++);
  }

  return get_symbol (table, id);
}

int in_global_scope (struct symbol_table * table) {
  return table->scopes->count <= 1;
}

void leave_scope (struct symbol_table * table) {
  scope_free (vector_pop (table->scopes));
}

int tmp_symbol (struct symbol_table * table) {
  return table->next ++;
}
