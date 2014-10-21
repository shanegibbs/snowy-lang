#ifndef NODES_H
#define NODES_H

typedef enum {
  IDENT,
  EXPRESSION
} NodeType;

typedef enum {
  INT_LITERAL
} ExpressionType;


typedef struct _Node {
  NodeType type;
  void *value;
} Node;

typedef struct _Expression {
  ExpressionType type;
  void *value;
} Expression;


Node* opal_ident_new(char *name);

typedef struct _IntLiteral {
    int value;
} IntLiteral;

Expression* opal_int_literal_new(char *value);

void exp_op_exp(Expression* lhs, int op, Expression *rhs);

#endif
