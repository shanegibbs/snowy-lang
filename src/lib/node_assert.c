#include <glib.h>

#include "node_assert.h"

void opal_assert_valid_node(Node *n)
{
  g_assert_nonnull(n);
  // n->node_next
  g_assert_cmpuint(n->node_type, >, NODE_TYPE_NULL);
  g_assert_cmpuint(n->node_type, <, NODE_TYPE_ENUM_MAX);
  switch(n->node_type) {
    case NODE_TYPE_STATEMENT:
      opal_assert_valid_statement((Statement*)n);
      break;
    case NODE_TYPE_EXPRESSION:
      opal_assert_valid_expression((Expression*)n);
      break;
    default:
      g_assert_not_reached();
      break;
  }
}

void opal_assert_valid_statement(Statement *s)
{
  g_assert(s->node_type == NODE_TYPE_STATEMENT);
}

void opal_assert_valid_expression(Expression *e)
{
  g_assert(e->node_type == NODE_TYPE_EXPRESSION);
}

void opal_assert_valid_ident(Ident *i)
{
  g_assert(i->node_type == NODE_TYPE_EXPRESSION);
  g_assert(i->expr_type == EXPR_TYPE_IDENT);
  g_assert_nonnull(i->value);
}
