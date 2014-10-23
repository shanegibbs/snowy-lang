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
  STATEMENT
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

typedef struct _Node {
  NodeType type;
  void *value; // Statement
} Node;

typedef struct _Statement {
  StatementType type;
  void *value; // DeclareVar, Expression
} Statement;

typedef struct _Expression {
  ExpressionType type;
  void *value; // IntLiteral, Tuple
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
  Expression *parent;
  int value;
} IntLiteral;

/* functions */

char* opal_ident_new(char *name);

IntLiteral* opal_int_literal_new(char *value);

Tuple* opal_tuple_new(Expression* lhs, NumOp num_op, Expression *rhs);

NumOp opal_num_op_from_string(char* value);

DeclarVar* opal_declare_var_new(char *id, Expression *e);

Statement *root;

#endif
