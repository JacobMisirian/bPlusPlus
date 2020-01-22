#ifndef _CODEGEN_H_
#define _CODEGEN_H_

#include <parser/ast_node.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/vector.h>

struct codegen {
  struct ast_node * ast;
};

struct codegen * codegen_init (struct ast_node * ast);
void             codegen_free (struct codegen  * codegen);

void codegen_run (struct codegen * codegen);

#endif
