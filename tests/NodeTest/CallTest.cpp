#include <stdio.h>
#include <string.h>

#include <SnowyAssert.h>

#include <Nodes/Call.h>
#include <Nodes/IntLiteral.h>
#include <Nodes/Ident.h>
#include <Nodes/Args.h>

using namespace Snowy;
using namespace std;

void call_no_arg_test(void)
{
    Call call(new Ident(new string("puts")), new Args());

    const char* expected = "Call=[name=[Ident[puts]],args=[Args[size=0]]]\n";
    const char* actual = call.to_string();
    s_assert_cmpstr(actual, expected);
    delete[] actual;
}

void call_single_arg_test(void)
{
    Call call(new Ident(new string("puts")), new Args(new IntLiteral(new string(("5")))));

    const char* expected = "Call=[name=[Ident[puts]],args=[Args[size=1,arg0=[IntLiteral=[5]]]]]\n";
    const char* actual = call.to_string();
    s_assert_cmpstr(actual, expected);
    delete[] actual;
}

void call_three_arg_test(void)
{
    Args* args = new Args(new IntLiteral(new string("1")));
    args->addArg(new IntLiteral(new string("2")));
    args->addArg(new IntLiteral(new string("3")));
    Call call(new Ident(new string("puts")), args);

    const char* expected = "Call=[name=[Ident[puts]],args=[Args[size=3,arg0=[IntLiteral=[1]],arg1=[IntLiteral=[2]],arg2=[IntLiteral=[3]]]]]\n";
    const char* actual = call.to_string();
    s_assert_cmpstr(actual, expected);
    delete[] actual;
}
