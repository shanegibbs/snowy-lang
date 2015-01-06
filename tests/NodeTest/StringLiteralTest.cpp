#include <stdio.h>

#include <SnowyAssert.h>

#include <Nodes/StringLiteral.h>

using namespace Snowy;

void string_literal_to_string(void)
{
    StringLiteral s("\"this is a test\"");
    s_assert_cmpstr(s.to_string(), "StringLiteral=[\"this is a test\"]\n");
}
