#include <parser/parser.h>

struct parser * init_parser (struct vector * tokens) {
  struct parser * parser;

  parser = calloc (1, sizeof (struct parser));

  parser->tokens = tokens;
  parser->pos    = 0;
  parser->len    = tokens->count;

  return parser;
}

void free_parser (struct parser * parser) {
  free (parser);
}

static struct ast_node * parse_statement (struct parser * parser);
static struct ast_node * parse_block     (struct parser * parser);
static struct ast_node * parse_for       (struct parser * parser);
static struct ast_node * parse_if        (struct parser * parser);
static struct ast_node * parse_meth_decl (struct parser * parser);
static struct ast_node * parse_return    (struct parser * parser);
static struct ast_node * parse_while     (struct parser * parser);
static struct ast_node * parse_expr_stmt (struct parser * parser);

static struct ast_node * parse_expr   (struct parser * parser);
static struct ast_node * parse_assign (struct parser * parser);
static struct ast_node * parse_or     (struct parser * parser);

static bool match_tok                (struct parser * parser, token_type_t type);
static bool match_tok_val            (struct parser * parser, token_type_t type, char * val);
static bool accept_tok               (struct parser * parser, token_type_t type);
static bool accept_tok_val           (struct parser * parser, token_type_t type, char * val);
static struct token * expect_tok     (struct parser * parser, token_type_t type);
static struct token * expect_tok_val (struct parser * parser, token_type_t type, char * val);
static bool eof                      (struct parser * parser);
static struct token * current_tok    (struct parser * parser);

struct ast_node * parse (struct parser * parser) {
  struct vector * children;

  children = init_vector ();
  while (parser->pos < parser->len) {
    vector_push (children, parse_statement (parser));
  }

  return init_ast_node (BLOCK_NODE, 0, 1, children);
}

static struct ast_node * parse_statement (struct parser * parser) {
  struct ast_node * ret;

  if (match_tok (parser, TOK_OBRACE)) {
    ret = parse_block (parser);
  } else if (match_tok_val (parser, TOK_IDENTIFIER, "for")) {
    ret = parse_for (parser);
  } else if (match_tok_val (parser, TOK_IDENTIFIER, "if")) {
    ret = parse_if (parser);
  } else if (match_tok_val (parser, TOK_IDENTIFIER, "func")) {
    ret = parse_meth_decl (parser);
  } else if (match_tok_val (parser, TOK_IDENTIFIER, "return")) {
    ret = parse_return (parser);
  } else if (match_tok_val (parser, TOK_IDENTIFIER, "while")) {
    ret = parse_while (parser);
  } else {
    ret = parse_expr_stmt (parser);
  }

  accept_tok (parser, TOK_SEMICOLON);

  return ret;
}

static struct ast_node * parse_block (struct parser * parser) {
  struct vector * children;

  children = init_vector ();

  expect_tok (parser, TOK_OBRACE);
  while (!accept_tok (parser, TOK_CBRACE)) {
    vector_push (children, parse_statement (parser));
  }

  return init_ast_node (BLOCK_NODE, 0, 1, children);
}

static struct ast_node * parse_for (struct parser * parser) {
  struct ast_node * init_stmt;
  struct ast_node * expr;
  struct ast_node * rep_stmt;
  struct ast_node * body;

  expect_tok_val              (parser, TOK_IDENTIFIER, "for");
  expect_tok                  (parser, TOK_OPAREN);
  init_stmt = parse_statement (parser);
  accept_tok                  (parser, TOK_SEMICOLON);
  expr      = parse_expr      (parser);
  accept_tok                  (parser, TOK_SEMICOLON);
  rep_stmt  = parse_statement (parser);
  expect_tok                  (parser, TOK_CPAREN);
  body      = parse_statement (parser);

  return init_ast_node (FOR_NODE, 0, 4, init_stmt, expr, rep_stmt, body);
}

static struct ast_node * parse_if (struct parser * parser) {
  struct ast_node * expr;
  struct ast_node * if_body;
  struct ast_node * else_body;

  expect_tok_val            (parser, TOK_IDENTIFIER, "if");
  expect_tok                (parser, TOK_OPAREN);
  expr    = parse_expr      (parser);
  expect_tok                (parser, TOK_CPAREN);
  if_body = parse_statement (parser);

  if (accept_tok_val (parser, TOK_IDENTIFIER, "else")) {
    else_body = parse_statement (parser);
  } else {
    else_body = NULL;
  }

  return init_ast_node (IF_NODE, 0, 3, expr, if_body, else_body);
}

static struct ast_node * parse_meth_decl (struct parser * parser) {
  char                * name;
  struct vector       * params;
  struct method_param * param;
  char                * return_type;
  struct ast_node     * body;

  params   = init_vector ();

  expect_tok_val (parser, TOK_IDENTIFIER, "func");
  name = copy_string (expect_tok (parser, TOK_IDENTIFIER)->val);
  expect_tok (parser, TOK_OPAREN);
  while (!accept_tok (parser, TOK_CPAREN)) {
    param = calloc (1, sizeof (struct method_param));
    if (accept_tok_val (parser, TOK_OP, "*")) {
      param->param_type = pointer_param;
    } else {
      param->param_type = regular_param;
    }

    param->id   = copy_string (expect_tok (parser, TOK_IDENTIFIER)->val);
    expect_tok                (parser, TOK_COLON);
    param->type = copy_string (expect_tok (parser, TOK_IDENTIFIER)->val);

    accept_tok (parser, TOK_COMMA);
  }
  expect_tok (parser, TOK_COLON);
  return_type = copy_string (expect_tok (parser, TOK_IDENTIFIER)->val);
  body        = parse_statement (parser);

  return init_ast_node (METH_DECL_NODE, 0, 4, name, params, return_type, body);
}

static struct ast_node * parse_return (struct parser * parser) {
  struct ast_node * expr;

  expect_tok_val (parser, TOK_IDENTIFIER, "return");
  expr = parse_expr (parser);

  return init_ast_node (RETURN_NODE, 0, 1, expr);
}

static struct ast_node * parse_while (struct parser * parser) {
  struct ast_node * expr;
  struct ast_node * body;

  expect_tok_val         (parser, TOK_IDENTIFIER, "while");
  expect_tok             (parser, TOK_OPAREN);
  expr = parse_expr      (parser);
  expect_tok             (parser, TOK_CPAREN);
  body = parse_statement (parser);

  return init_ast_node (WHILE_NODE, 0, 2, expr, body);
}

static struct ast_node * parse_expr_stmt (struct parser * parser) {
  struct ast_node * expr;

  expr = parse_expr (parser);
  accept_tok (parser, TOK_SEMICOLON);

  return init_ast_node (EXPR_STMT_NODE, 0, 1, expr);
}

static struct ast_node * parse_expr (struct parser * parser) {
  return parse_assign (parser);
}

static struct ast_node * parse_assign (struct parser * parser) {
  struct ast_node * left;
  char            * op;
  bin_op_type_t     op_type;

  left = parse_or (parser);

  if (match_tok (parser, TOK_ASSIGN)) {
    op       = expect_tok (parser, TOK_ASSIGN)->val;

    if (strcmp (op, "=") == 0) {
      return init_ast_node (ASSIGN_NODE, 0, 2, left, parse_assign (parser));
    } else {
      op_type = 0;

      if (strcmp (op, "+") == 0) {
        op_type = ADD_BIN_OP;
      } else if (strcmp (op, "&") == 0) {
        op_type = BITWISE_AND_BIN_OP;
      } else if (strcmp (op, "|") == 0) {
        op_type = BITWISE_OR_BIN_OP;
      } else if (strcmp (op, "/") == 0) {
        op_type = DIV_BIN_OP;
      } else if (strcmp (op, "%") == 0) {
        op_type = MOD_BIN_OP;
      } else if (strcmp (op, "*") == 0) {
        op_type = MUL_BIN_OP;
      } else if (strcmp (op, "-") == 0) {
        op_type = SUB_BIN_OP;
      } else if (strcmp (op, "^") == 0) {
        op_type = XOR_BIN_OP;
      }

    }
  }
}

static struct ast_node * parse_or (struct parser * parser) {
  
}

static bool match_tok (struct parser * parser, token_type_t type) {
  if (eof (parser)) { return false; }

  return current_tok (parser)->type == type;
}

static bool match_tok_val (struct parser * parser, token_type_t type, char * val) {
  if (eof (parser)) { return false; }

  return (current_tok (parser)->type == type) && (strcmp (current_tok (parser)->val, val) == 0);
}

static bool accept_tok (struct parser * parser, token_type_t type) {
  if (match_tok (parser, type)) {
    parser->pos ++;
    return true;
  }

  return false;
}

static bool accept_tok_val (struct parser * parser, token_type_t type, char * val) {
  if (match_tok_val (parser, type, val)) {
    parser->pos ++;
    return true;
  }

  return false;
}

static struct token * expect_tok (struct parser * parser, token_type_t type) {
  if (match_tok (parser, type)) {
    return current_tok (parser);
  }

  printf ("Parser Error! Expected token of type %d, got %d with value \"%s\"\n",
          type,
          current_tok (parser)->type,
          current_tok (parser)->val);
  exit (0);
}

static struct token * expect_tok_val (struct parser * parser, token_type_t type, char * val) {
  if (match_tok_val (parser, type, val)) {
    return current_tok (parser);
  }

  printf ("Parser Error! Expected token of type %d with value \"%s\", got %d with value \"%s\"\n",
          type,
          val,
          current_tok (parser)->type,
          current_tok (parser)->val);
  exit (0);
}

static bool eof (struct parser * parser) {
  return parser->pos >= parser->len;
}

static struct token * current_tok (struct parser * parser) {
  return (struct token *)vector_get (parser->tokens, parser->pos);
}
