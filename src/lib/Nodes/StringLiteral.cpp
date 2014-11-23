#include <glib.h>

#include "StringLiteral.h"

namespace Snowy
{

StringLiteral::StringLiteral(const char* v)
{
    g_assert_nonnull(v);
    g_assert_cmpint(strlen(v), >, 0);
    g_assert_cmpint(strlen(v), <, 100);

    val = (const char*) malloc(strlen(v) + 1);
    strncpy((char*)val, v, strlen(v));
}


void StringLiteral::to_sstream(std::ostringstream* s)
{
    g_assert_nonnull(val);
    g_assert_cmpint(strlen(val), >, 0);
    g_assert_cmpint(strlen(val), <, 100);

    *s << "StringLiteral=[" << val << "]";
}

}
