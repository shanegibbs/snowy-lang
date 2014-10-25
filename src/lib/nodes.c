#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "nodes.h"
#include "parser.h"
#include "tokens.h"

void  opal_stdin_parse()
{
    printf("Reading from stdin\n");
    opal_bison_parse();
}

Node* opal_parse_string(const char *code)
{
    opal_flex__scan_string(code);
    opal_bison_parse();
    return root;
}

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
