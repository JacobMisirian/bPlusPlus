#ifndef _AST_NODE_H_
#define _AST_NODE_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <util/vector.h>

typedef enum {
  ACCESS_NODE,    ASSIGN_NODE, BIN_OP_NODE,    BLOCK_NODE,     BREAK_NODE,    CONTINUE_NODE,
  EXPR_STMT_NODE, FOR_NODE,    METH_CALL_NODE, METH_DECL_NODE, ID_NODE,       IF_NODE,
  INDEX_NODE,     INT_NODE,    RETURN_NODE,    STRING_NODE,    UNARY_OP_NODE, WHILE_NODE,
  VAR_DECL_NODE,
} node_type_t;

typedef enum {
  ADD_BIN_OP,             BITWISE_AND_BIN_OP, BITWISE_OR_BIN_OP,       DIV_BIN_OP,
  EQUALITY_BIN_OP,        GREATER_BIN_OP,     GREATER_OR_EQUAL_BIN_OP, LESSER_BIN_OP,
  LESSER_OR_EQUAL_BIN_OP, MOD_BIN_OP,         MUL_BIN_OP,              SUB_BIN_OP,
  XOR_BIN_OP,
} bin_op_type_t;

typedef enum {
  BITWISE_NOT_UNARY_OP, LOGICAL_NOT_UNARY_OP,
} unary_op_type_t;

typedef enum {
  pointer_param, regular_param,
} param_type_t;

struct method_param {
  param_type_t   param_type;
  char         * id;
  char         * type;
};

struct ast_node {
  node_type_t     type;
  struct vector * children;
  int             arg;
};

struct ast_node * ast_node_init (node_type_t type, int arg, int child_count, ...);
void              ast_node_free (struct ast_node * ast_node);

#endif
