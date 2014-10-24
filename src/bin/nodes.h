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
  STATEMENT_TYPE_VAR_DECLAR
} StatementType;

typedef enum {
    EXPR_TYPE_IDENT,
    INT_LITERAL,
    EXPR_TYPE_TUPLE
} ExpressionType;

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

/* functions */

Ident* opal_ident_new(char *name);

IntLiteral* opal_int_literal_new(char *value);

Tuple* opal_tuple_new(Expression* lhs, NumOp num_op, Expression *rhs);

NumOp opal_num_op_from_string(char* value);

DeclarVar* opal_declare_var_new(Ident *id, Expression *e);

void opal_assert_ident(Ident *i);

void opal_set_root(Node *n);
void opal_add_node(Node *last, Node *node);

char* get_num_op_desc(NumOp op);
char* get_ident_desc(Ident *i);
char* get_int_literal_desc(IntLiteral *i);
char* get_tuple_desc(Tuple *t);
char* get_var_declar_desc(DeclarVar *d);
char* get_expr_desc(Expression *e);
char* get_statement_desc(Statement *s);
char* get_node_desc(Node *node);

Node *root;

#endif
