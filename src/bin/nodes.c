#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "nodes.h"

char* opal_ident_new(char *name)
{
    char* n = malloc((sizeof(char) * strlen(name)) + 1);
    strncpy(n, name, strlen(name));
    printf("{ident %s}\n", n);

    /*
    Node *n = malloc(sizeof(Node));
    n->type = IDENT;
    n->value = name;
    */

    return n;
}

IntLiteral* opal_int_literal_new(char *value)
{
    printf("{int exp %s}\n", value);

    Statement *s = malloc(sizeof(Statement));
    s->type = EXPRESSION;

    Expression *e = malloc(sizeof(Expression));
    e->type = INT_LITERAL;
    s->value = e;

    IntLiteral *i = malloc(sizeof(IntLiteral));
    i->parent = e;
    i->value = atoi(value);
    e->value = i;

    return i;
}

NumOp opal_num_op_from_string(char* value)
{
    printf("{num_op %s}\n", value);

    if (value[0] == '+') {
        return PLUS;
    } else if (value[0] == '-') {
        return MINUS;
    } else if (value[0] == '*') {
        return MULTIPLY;
    } else if (value[0] == '/') {
        return DIVIDE;
    } else {
        return 0;
    }
}

Tuple* opal_tuple_new(Expression* lhs, NumOp num_op, Expression *rhs)
{
    char op = 0;
    if (num_op == PLUS) {
        op = '+';
    } else if (num_op == MINUS) {
        op = '-';
    } else if (num_op == MULTIPLY) {
        op = '*';
    } else if (num_op == DIVIDE) {
        op = '/';
    }

    printf("{exp '%c' exp}\n", op);

    Statement *s = malloc(sizeof(Statement));
    s->type = EXPRESSION;

    Expression *e = malloc(sizeof(Expression));
    e->type = TUPLE;
    s->value = e;

    Tuple *t = malloc(sizeof(Tuple));
    t->parent = e;
    t->lhs = lhs;
    t->num_op = num_op;
    t->rhs = rhs;
    e->value = t;

    return t;
}

DeclarVar* opal_declare_var_new(char *id, Expression *e)
{
    Statement *s = malloc(sizeof(Statement));
    s->type = EXPRESSION;

    DeclarVar *d = malloc(sizeof(DeclarVar));
    d->parent = s;
    d->id = id;
    d->e = e;
    s->value = d;

    printf("{var_decl '%s'}\n", d->id);
    return d;
}
