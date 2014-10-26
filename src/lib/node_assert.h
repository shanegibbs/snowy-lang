#ifndef NODE_ASSERT_H
#define NODE_ASSERT_H

#include "structs.h"

/* assert functions */

void opal_assert_valid_node(Node *n);
void opal_assert_valid_statement(Statement *s);
void opal_assert_valid_expression(Expression *n);
void opal_assert_valid_ident(Ident *i);

#endif
