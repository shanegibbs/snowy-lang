#include <stdio.h>
#include <string>

#include <SnowyAssert.h>

#include <Nodes/IntLiteral.h>

using namespace Snowy;

void int_literal_test(void)
{
    IntLiteral i("3");
    s_assert_cmpstr(i.to_string(), "IntLiteral=[3]\n");
}

void int_literal_multi_test(void)
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
