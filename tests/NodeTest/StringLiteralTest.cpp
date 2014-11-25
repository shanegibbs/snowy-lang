#include <glib.h>
#include <stdio.h>
#include <glib/gstdio.h>

#include <Nodes/StringLiteral.h>

using namespace Snowy;

void string_literal_to_string(void)
{
    StringLiteral s("\"this is a test\"");
    g_assert_cmpstr(s.to_string(), ==, "StringLiteral=[\"this is a test\"]\n");
}
