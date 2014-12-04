#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include "Type.h"
#include <Log.h>

namespace Snowy
{

const Log Type::log = Log("Type");

Type::Type(const char* n)
{
    log.debug("Creating Type with id '%s'", n);

    g_assert_nonnull(n);
    g_assert_cmpint(strlen(n), >, 0);
    g_assert_cmpint(strlen(n), <, 100);

    id = (const char*) malloc(strlen(n) + 1);
    strncpy((char*)id, n, strlen(n));
}

void Type::to_sstream(std::ostringstream* s) const
{
    g_assert_nonnull(id);
    g_assert_cmpint(strlen(id), >, 0);
    g_assert_cmpint(strlen(id), <, 100);

    *s << "Type[" << id << "]";
}

}
