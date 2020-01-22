#ifndef _SCOPE_H_
#define _SCOPE_H_

#include <stdlib.h>
#include <string.h>

#define SCOPE_SIZE 20

struct scope {
  char ** ids;
  int   * vals;
  int     length;
  int     size;
};

struct scope * scope_init ();
void           scope_free (struct scope * scope);

int  scope_get (struct scope * scope, char * id);
void scope_set (struct scope * scope, char * id, int val);

#endif
