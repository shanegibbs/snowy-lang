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
    IntLiteral *i = malloc(sizeof(IntLiteral));
    i->node_next = NULL;
    i->node_type = NODE_TYPE_EXPRESSION;
    i->expr_type = INT_LITERAL;
    i->value = atoi(value);

    printf("Parsed: %s\n", get_int_literal_desc(i));

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
    // e->type = TUPLE;
    s->value = e;

    Tuple *t = malloc(sizeof(Tuple));
    t->parent = e;
    t->lhs = lhs;
    t->num_op = num_op;
    t->rhs = rhs;
    // e->value = t;

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

void opal_add_node(Node *last, Node *node)
{
    printf("Linking %s -> %s\n",
           get_node_desc(last),
           get_node_desc(node));
    last->node_next = node;
}

void opal_set_root(Node *n)
{
    printf("Setting root\n");
    root = n;
}

char* get_int_literal_desc(IntLiteral *i)
{
    char *desc = malloc(128);
    sprintf(desc, "Int %d", i->value);
    return desc;
}

char* get_expr_desc(Expression *e)
{
    switch (e->expr_type) {
    case INT_LITERAL:
        return get_int_literal_desc((IntLiteral*)e);
    default:
        return "Unknown expression type";
    }
}

char* get_node_desc(Node *node)
{
    switch (node->node_type) {
        case NODE_TYPE_EXPRESSION:
            return get_expr_desc((Expression*)node);
        default:
            return "unknown node type";
    }
}
