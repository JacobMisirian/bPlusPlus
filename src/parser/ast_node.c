#include <parser/ast_node.h>

struct ast_node * ast_node_init (node_type_t type, int arg, int child_count, ...) {
  struct ast_node * ast_node;
  struct vector   * children;
  va_list           cl;

  va_start (cl, child_count);

  children = vector_init ();
  ast_node = calloc (1, sizeof (struct ast_node));

  ast_node->type     = type;
  ast_node->children = children;

  for (int i = 0; i < child_count; i++) {
    vector_push (children, va_arg (cl, void *));
  }

  va_end (cl);

  return ast_node;
}

void ast_node_free (struct ast_node * ast_node) {

}
