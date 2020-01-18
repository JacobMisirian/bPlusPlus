#include <emit/codegen.h>

struct codegen * init_codegen (struct ast_node * ast) {
  struct codegen * codegen;

  codegen      = calloc (1, sizeof (struct codegen));

  codegen->ast = ast;

  return codegen;
}

static void accept_ast_node       (struct codegen * codegen, struct ast_node * node);
static void accept_access_node    (struct codegen * codegen, struct ast_node * node);
static void accept_assign_node    (struct codegen * codegen, struct ast_node * node);
static void accept_bin_op_node    (struct codegen * codegen, struct ast_node * node);
static void accept_block_node     (struct codegen * codegen, struct ast_node * node);
static void accept_break_node     (struct codegen * codegen, struct ast_node * node);
static void accept_continue_node  (struct codegen * codegen, struct ast_node * node);
static void accept_expr_stmt_node (struct codegen * codegen, struct ast_node * node);
static void accept_for_node       (struct codegen * codegen, struct ast_node * node);
static void accept_meth_call_node (struct codegen * codegen, struct ast_node * node);
static void accept_meth_decl_node (struct codegen * codegen, struct ast_node * node);
static void accept_id_node        (struct codegen * codegen, struct ast_node * node);
static void accept_if_node        (struct codegen * codegen, struct ast_node * node);
static void accept_index_node     (struct codegen * codegen, struct ast_node * node);
static void accept_int_node       (struct codegen * codegen, struct ast_node * node);
static void accept_return_node    (struct codegen * codegen, struct ast_node * node);
static void accept_string_node    (struct codegen * codegen, struct ast_node * node);
static void accept_unary_op_node  (struct codegen * codegen, struct ast_node * node);
static void accept_while_node     (struct codegen * codegen, struct ast_node * node);
static void accept_var_decl_node  (struct codegen * codegen, struct ast_node * node);

void free_codegen (struct codegen * codegen) {
  free_ast_node (codegen->ast);
  free          (codegen);
}

void codegen_run (struct codegen * codegen) {
  accept_ast_node (codegen, codegen->ast);
}

static void accept_ast_node (struct codegen * codegen, struct ast_node * node) {
  switch (node->type) {
    case ACCESS_NODE:
      accept_access_node    (codegen, node);
      break;
    case ASSIGN_NODE:
      accept_assign_node    (codegen, node);
      break;
    case BIN_OP_NODE:
      accept_bin_op_node    (codegen, node);
      break;
    case BLOCK_NODE:
      accept_block_node     (codegen, node);
      break;
    case BREAK_NODE:
      accept_break_node     (codegen, node);
      break;
    case CONTINUE_NODE:
      accept_continue_node  (codegen, node);
      break;
    case EXPR_STMT_NODE:
      accept_expr_stmt_node (codegen, node);
      break;
    case FOR_NODE:
      accept_for_node       (codegen, node);
      break;
    case METH_CALL_NODE:
      accept_meth_call_node (codegen, node);
      break;
    case METH_DECL_NODE:
      accept_meth_decl_node (codegen, node);
      break;
    case ID_NODE:
      accept_id_node        (codegen, node);
      break;
    case IF_NODE:
      accept_if_node        (codegen, node);
      break;
    case INDEX_NODE:
      accept_index_node     (codegen, node);
      break;
    case INT_NODE:
      accept_int_node       (codegen, node);
      break;
    case RETURN_NODE:
      accept_return_node    (codegen, node);
      break;
    case STRING_NODE:
      accept_string_node    (codegen, node);
      break;
    case UNARY_OP_NODE:
      accept_unary_op_node  (codegen, node);
      break;
    case WHILE_NODE:
      accept_while_node     (codegen, node);
      break;
    case VAR_DECL_NODE:
      accept_var_decl_node  (codegen, node);
      break;
  }
}

static void accept_access_node    (struct codegen * codegen, struct ast_node * node){}
static void accept_assign_node    (struct codegen * codegen, struct ast_node * node){}
static void accept_bin_op_node    (struct codegen * codegen, struct ast_node * node){}
static void accept_block_node     (struct codegen * codegen, struct ast_node * node){}
static void accept_break_node     (struct codegen * codegen, struct ast_node * node){}
static void accept_continue_node  (struct codegen * codegen, struct ast_node * node){}
static void accept_expr_stmt_node (struct codegen * codegen, struct ast_node * node){}
static void accept_for_node       (struct codegen * codegen, struct ast_node * node){}
static void accept_meth_call_node (struct codegen * codegen, struct ast_node * node){}
static void accept_meth_decl_node (struct codegen * codegen, struct ast_node * node){}
static void accept_id_node        (struct codegen * codegen, struct ast_node * node){}
static void accept_if_node        (struct codegen * codegen, struct ast_node * node){}
static void accept_index_node     (struct codegen * codegen, struct ast_node * node){}
static void accept_int_node       (struct codegen * codegen, struct ast_node * node){}
static void accept_return_node    (struct codegen * codegen, struct ast_node * node){}
static void accept_string_node    (struct codegen * codegen, struct ast_node * node){}
static void accept_unary_op_node  (struct codegen * codegen, struct ast_node * node){}
static void accept_while_node     (struct codegen * codegen, struct ast_node * node){}
static void accept_var_decl_node  (struct codegen * codegen, struct ast_node * node){}
