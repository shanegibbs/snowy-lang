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
