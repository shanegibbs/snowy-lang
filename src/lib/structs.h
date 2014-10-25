#ifndef STRUCTS_H
#define STRUCTS_H

#include "enums.h"

/* structs */

typedef struct _Node Node;

#define NODE_MEMBERS Node *node_next; NodeType node_type;
#define EXPRESSION_MEMBERS NODE_MEMBERS ExpressionType expr_type;

#define STATEMENT_MEMBERS NODE_MEMBERS StatementType statement_type;

struct _Node {
    NODE_MEMBERS
};

typedef struct _Expression { /* extnds Node */
    EXPRESSION_MEMBERS
} Expression;

typedef struct _Ident { /* extends Expression */
    EXPRESSION_MEMBERS
    char *value;
} Ident;

typedef struct _Tuple { /* extends Expression */
    EXPRESSION_MEMBERS
    Expression *lhs;
    NumOp num_op;
    Expression *rhs;
} Tuple;

typedef struct _IntLiteral { /* extends Expression */
    EXPRESSION_MEMBERS
    int value;
} IntLiteral;

typedef struct _Statement { /* extends Node */
    STATEMENT_MEMBERS
} Statement;

typedef struct _DeclareVar { /* extends Statement */
    STATEMENT_MEMBERS
    Ident *id;
    Expression *e;
} DeclarVar;

#endif
