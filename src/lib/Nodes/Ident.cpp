#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "Ident.h"

namespace Snowy
{

Ident::Ident(const char* n)
{
    g_assert_nonnull(n);
    g_assert_cmpint(strlen(n), >, 0);
    g_assert_cmpint(strlen(n), <, 100);

    name = (const char*) malloc(strlen(n) + 1);
    strncpy((char*)name, n, strlen(n));
}

void Snowy::Ident::to_sstream(std::ostringstream* s) const
{
    g_assert_nonnull(name);
    g_assert_cmpint(strlen(name), >, 0);
    g_assert_cmpint(strlen(name), <, 100);

    *s << "Ident[" << name << "]";
}

}
