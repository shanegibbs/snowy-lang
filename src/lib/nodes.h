#ifndef NODES_H
#define NODES_H

#include "enums.h"
#include "structs.h"

/* functions */

void  opal_stdin_parse();
Node* opal_parse_string(const char *code);


/* graph functions */

Ident*      opal_ident_new(char *name);
IntLiteral* opal_int_literal_new(char *value);
Tuple*      opal_tuple_new(Expression* lhs, NumOp num_op, Expression *rhs);
NumOp       opal_num_op_from_string(char* value);
DeclarVar*  opal_declare_var_new(Ident *id, Expression *e);
void        opal_set_root(Node *n);
void        opal_add_node(Node *last, Node *node);


/* assert functions */

void opal_assert_ident(Ident *i);


/* description functions */

char* get_num_op_desc(NumOp op);
char* get_ident_desc(Ident *i);
char* get_int_literal_desc(IntLiteral *i);
char* get_tuple_desc(Tuple *t);
char* get_var_declar_desc(DeclarVar *d);
char* get_expr_desc(Expression *e);
char* get_statement_desc(Statement *s);
char* get_node_desc(Node *node);
char* get_prog_desc(Node *root);

Node *root;

#endif
