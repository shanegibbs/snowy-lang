#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <glib/gstdio.h>

#include <Nodes/Call.h>
#include <Nodes/IntLiteral.h>

using namespace Snowy;
using namespace std;

void snowy_diff_string(const char* actual, const char* expected)
{
    if (strcmp(actual, expected) != 0) {
        printf("\nActual:   '%s'\n", actual);
        printf("Expected: '%s'\n", expected);
    }
    g_assert_cmpstr(actual, ==, expected);
}

void call_no_arg_test(void)
{
    Ident name("puts");
    Args args;
    Call call(&name, &args);

    const char* expected = "Call=[name=[Ident[puts]],args=[Args[size=0]]]\n";
    snowy_diff_string(call.to_string(), expected);
}

void call_single_arg_test(void)
{
    Ident name("puts");
    IntLiteral five("5");
    Args args(&five);
    Call call(&name, &args);

    const char* expected = "Call=[name=[Ident[puts]],args=[Args[size=1,arg0=[IntLiteral=[5]]]]]\n";
    snowy_diff_string(call.to_string(), expected);
}

void call_three_arg_test(void)
{
    Ident name("puts");
    IntLiteral one("1");
    IntLiteral two("2");
    IntLiteral three("3");
    Args args(&one);
    args.addArg(&two);
    args.addArg(&three);
    Call call(&name, &args);

    const char* expected = "Call=[name=[Ident[puts]],args=[Args[size=3,arg0=[IntLiteral=[1]],arg1=[IntLiteral=[2]],arg2=[IntLiteral=[3]]]]]\n";
    snowy_diff_string(call.to_string(), expected);
}
