#ifndef NODES_H
#define NODES_H

/* enums */

typedef enum {
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE
} NumOp;

typedef enum {
  NODE_TYPE_STATEMENT,
  NODE_TYPE_EXPRESSION
} NodeType;

typedef enum {
  IDENT,
  EXPRESSION
} StatementType;

typedef enum {
  INT_LITERAL,
  TUPLE
} ExpressionType;

/* structs */

typedef struct _Node Node;

#define NODE_MEMBERS Node *node_next; NodeType node_type;

struct _Node {
  NODE_MEMBERS
};

typedef struct _Statement {
  StatementType type;
  void *value; // DeclareVar, Expression
} Statement;

typedef struct _Expression {
  NODE_MEMBERS
  ExpressionType expr_type;
} Expression;

typedef struct _Tuple {
  Expression *parent;
  Expression *lhs;
  NumOp num_op;
  Expression *rhs;
} Tuple;

typedef struct _DeclareVar {
  Statement *parent;
  char *id;
  Expression *e;
} DeclarVar;

typedef struct _IntLiteral {
  NODE_MEMBERS
  ExpressionType expr_type;

  int value;
} IntLiteral;

/* functions */

char* opal_ident_new(char *name);

IntLiteral* opal_int_literal_new(char *value);

Tuple* opal_tuple_new(Expression* lhs, NumOp num_op, Expression *rhs);

NumOp opal_num_op_from_string(char* value);

DeclarVar* opal_declare_var_new(char *id, Expression *e);

void opal_set_root(Node *n);
void opal_add_node(Node *last, Node *node);

char* get_int_literal_desc(IntLiteral *i);
char* get_expr_desc(Expression *e);
char* get_node_desc(Node *node);

Node *root;

#endif
