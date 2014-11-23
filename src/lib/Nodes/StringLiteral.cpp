#include <glib.h>

#include "StringLiteral.h"

namespace Snowy
{

StringLiteral::StringLiteral(const char* v)
{
    g_assert_nonnull(v);
    g_assert_cmpint(strlen(v), >, 0);
    g_assert_cmpint(strlen(v), <, 100);

    char* new_val = (char*)malloc(strlen(v) + 1);
    strncpy((char*)new_val, v, strlen(v));
    new_val[strlen(v)] = 0;

    val = (const char*)new_val;
}


void StringLiteral::to_sstream(std::ostringstream* s)
{
    g_assert_nonnull(val);
    g_assert_cmpint(strlen(val), >, 0);
    g_assert_cmpint(strlen(val), <, 100);

    *s << "StringLiteral=[" << val << "]";
}

}
