#include <glib.h>
#include <stdio.h>
#include <glib/gstdio.h>

#include <Nodes/IntLiteral.h>

using namespace Snowy;

void int_literal_test(void)
{
    IntLiteral i("3");
    g_assert_cmpstr(i.to_string(), ==, "IntLiteral=[3]\n");
}

void int_literal_multi_test(void)
{
    IntLiteral a("1");
    IntLiteral b("2");
    IntLiteral c("3");

    a.setNext(&b);
    b.setNext(&c);

    const char* expected = "IntLiteral=[1]\nIntLiteral=[2]\nIntLiteral=[3]\n";
    const char* actual = a.to_program_string();
    g_assert_cmpstr(actual, ==, expected);
}
