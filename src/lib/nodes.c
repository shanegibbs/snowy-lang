#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "nodes.h"

Ident* opal_ident_new(char *name)
{
    Ident *i = malloc(sizeof(Ident));
    i->node_next = NULL;
    i->node_type = NODE_TYPE_EXPRESSION;
    i->expr_type = EXPR_TYPE_IDENT;

    char* n = malloc((sizeof(char) * strlen(name)) + 1);
    strncpy(n, name, strlen(name));
    i->value = n;

    printf("Parsed: %s\n", get_ident_desc(i));

    opal_assert_ident(i);
    g_assert(name != i->value);
    return i;
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

    Tuple *t = malloc(sizeof(Tuple));
    t->node_type = NODE_TYPE_EXPRESSION;
    t->expr_type = EXPR_TYPE_TUPLE;
    t->lhs = lhs;
    t->num_op = num_op;
    t->rhs = rhs;

    printf("Parsed: %s\n", get_tuple_desc(t));

    return t;
}

DeclarVar* opal_declare_var_new(Ident *id, Expression *e)
{
    opal_assert_ident(id);

    DeclarVar *d = malloc(sizeof(DeclarVar));
    d->node_type = NODE_TYPE_STATEMENT;
    d->statement_type = STATEMENT_TYPE_VAR_DECLAR;
    d->id = id;
    d->e = e;

    printf("Parsed: %s\n", get_var_declar_desc(d));
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

void opal_assert_ident(Ident *i)
{
    g_assert(i->node_type == NODE_TYPE_EXPRESSION);
    g_assert(i->expr_type == EXPR_TYPE_IDENT);
    g_assert_nonnull(i->value);
}

char* get_num_op_desc(NumOp op)
{
    switch(op){
        case PLUS: return "+";
        case MINUS: return "-";
        case MULTIPLY: return "*";
        case DIVIDE: return "/";
        default: return "unknown num_op";
    }
}

char* get_ident_desc(Ident *i)
{
    char *desc = malloc(128);
    sprintf(desc, "Ident=[%s]", i->value);
    return desc;
}

char* get_int_literal_desc(IntLiteral *i)
{
    char *desc = malloc(128);
    sprintf(desc, "IntLiteral=[%d]", i->value);
    return desc;
}

char* get_tuple_desc(Tuple *t)
{
    char *desc = malloc(1024);
    sprintf(desc, "Tuple=[lhs=[%s] op=[%s] rhs=[%s]]",
            get_expr_desc(t->lhs),
            get_num_op_desc(t->num_op),
            get_expr_desc(t->rhs));
    return desc;
}

char* get_var_declar_desc(DeclarVar *d)
{
    char *desc = malloc(1024);
    sprintf(desc, "Declare=[id=[%s] expr=[%s]]",
            get_ident_desc(d->id),
            get_expr_desc(d->e));
    return desc;
}

char* get_expr_desc(Expression *e)
{
    switch (e->expr_type) {
    case INT_LITERAL:
        return get_int_literal_desc((IntLiteral*)e);
    case EXPR_TYPE_TUPLE:
        return get_tuple_desc((Tuple*)e);
    default:
        return "Unknown expression type";
    }
}

char* get_statement_desc(Statement *s)
{
    switch(s->statement_type) {
        case STATEMENT_TYPE_VAR_DECLAR:
            return get_var_declar_desc((DeclarVar*)s);
    }

}

char* get_node_desc(Node *node)
{
    switch (node->node_type) {
        case NODE_TYPE_EXPRESSION:
            return get_expr_desc((Expression*)node);
        case NODE_TYPE_STATEMENT:
            return get_statement_desc((Statement*)node);
        default:
            return "unknown node type";
    }
}
