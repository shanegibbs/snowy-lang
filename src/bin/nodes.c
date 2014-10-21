#include <stdlib.h>
#include <stdio.h>

#include "nodes.h"

Node* opal_ident_new(char *name)
{
    printf("{ident %s}\n", name);

    Node *n = malloc(sizeof(Node));
    n->type = IDENT;
    n->value = name;

    return n;
}

Expression* opal_int_literal_new(char *value)
{
    printf("{int exp %s}\n", value);

    Expression *e = malloc(sizeof(Expression));
    e->type = INT_LITERAL;

    int *i = malloc(sizeof(int));
    *i = atoi(value);

    e->value = i;

    return e;
}

void exp_op_exp(Expression* lhs, int op, Expression *rhs)
{
    printf("boom\n");
}
