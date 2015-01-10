#include <stdio.h>
#include <string>

#include <SnowyAssert.h>

#include <Nodes/IntLiteral.h>

#include "SnowyTestSuite.h"

using namespace Snowy;

static void int_literal_test(void)
{
    IntLiteral i("3");
    const char* expected = "IntLiteral=[3]\n";
    const char* actual = i.to_string();
    s_assert_cmpstr(actual, expected);
    delete[] actual;
}

static void int_literal_multi_test(void)
{
    IntLiteral root("1");
    IntLiteral* b = new IntLiteral("2");
    IntLiteral* c = new IntLiteral("3");

    root.setNext(b);
    b->setNext(c);

    const string& expected = "IntLiteral=[1]\nIntLiteral=[2]\nIntLiteral=[3]\n";
    const string& actual = root.to_program_string();
    s_assert_cmpstr(actual, expected);
}

void node_int_literal_tests(TestSuite& tests)
{
    tests.add("/Nodes/IntLiteral/test", int_literal_test);
    tests.add("/Nodes/IntLiteral/multi", int_literal_multi_test);
}
