#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <glib.h>

#include "nodes.h"

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
        default:
            return "unknown statement";
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

char* get_prog_desc(Node *root)
{
    g_assert_nonnull(root);
    Node *node = root;
    char *desc = malloc(4096);
    desc[0] = 0;
    while (node != NULL) {
        sprintf(desc, "%s%s\n", desc, get_node_desc(node));
        node = node->node_next;
    }

    return desc;
}
