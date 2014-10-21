#include <stdlib.h>
#include <stdio.h>

#include "nodes.h"

Ident* opal_ident_new(char *name)
{
    printf("{ident %s}\n", name);
    Ident *n = malloc(sizeof(Ident));
    n->name = name;
    return n;
}

IntLiteral* opal_int_literal_new(char *value)
{
    printf("{int exp %s}\n", value);
    IntLiteral *n = malloc(sizeof(IntLiteral));

    return n;
}
