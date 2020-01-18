#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

#include <emit/scope.h>
#include <stdlib.h>
#include <util/vector.h>

struct symbol_table {
  struct vector * scopes;
  int             next;
};

struct symbol_table * init_symbol_table ();
void                  free_symbol_table (struct symbol_table * symbol_table);

void enter_scope     (struct symbol_table * table);
int  get_symbol      (struct symbol_table * table, char * id);
int  handle_symbol   (struct symbol_table * table, char * id);
int  has_symbol      (struct symbol_table * table, char * id);
int  in_global_scope (struct symbol_table * table);
void leave_scope     (struct symbol_table * table);
int  tmp_symbol      (struct symbol_table * table);

#endif
