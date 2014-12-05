#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "Ident.h"
#include <Log.h>

namespace Snowy
{

const Log Ident::log = Log("Ident");

Ident::Ident(const char* n)
{
    log.debug("Creating Ident with name '%s'", n);

    g_assert_nonnull(n);
    g_assert_cmpint(strlen(n), >, 0);
    g_assert_cmpint(strlen(n), <, 100);

    char* new_name = (char*) malloc(strlen(n) + 1);
    strncpy(new_name, n, strlen(n));
    name = new_name;
}

void Snowy::Ident::to_sstream(std::ostringstream* s) const
{
    g_assert_nonnull(name);
    g_assert_cmpint(strlen(name), >, 0);
    g_assert_cmpint(strlen(name), <, 100);

    *s << "Ident[" << name << "]";
}

}
