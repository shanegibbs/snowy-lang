#ifndef ENUMS_H
#define ENUMS_H

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
  STATEMENT_TYPE_VAR_DECLAR
} StatementType;

typedef enum {
    EXPR_TYPE_IDENT,
    INT_LITERAL,
    EXPR_TYPE_TUPLE
} ExpressionType;

#endif
