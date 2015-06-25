#include <stdio.h>

#include "SnowyTestSuite.h"

#include <SnowyAssert.h>

#include <Nodes/StringLiteral.h>

using namespace Snowy;

void string_literal_to_string(void)
{
    StringLiteral s(strptr("\"this is a test\""));
    const char* expected = "StringLiteral=[\"this is a test\"]\n";
    const char* actual = s.to_string();
    s_assert_cmpstr(actual, expected);
    delete[] actual;
}
