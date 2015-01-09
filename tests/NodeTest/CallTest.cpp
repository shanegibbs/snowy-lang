#include <stdio.h>
#include <string.h>

#include <SnowyAssert.h>

#include <Nodes/Call.h>
#include <Nodes/IntLiteral.h>

using namespace Snowy;
using namespace std;

void call_no_arg_test(void)
{
    Call call(new Ident("puts"), new Args());

    const char* expected = "Call=[name=[Ident[puts]],args=[Args[size=0]]]\n";
    s_assert_cmpstr(call.to_string(), expected);
}

void call_single_arg_test(void)
{
    Call call(new Ident("puts"), new Args(new IntLiteral("5")));

    const char* expected = "Call=[name=[Ident[puts]],args=[Args[size=1,arg0=[IntLiteral=[5]]]]]\n";
    s_assert_cmpstr(call.to_string(), expected);
}

void call_three_arg_test(void)
{
    Args* args = new Args(new IntLiteral("1"));
    args->addArg(new IntLiteral("2"));
    args->addArg(new IntLiteral("3"));
    Call call(new Ident("puts"), args);

    const char* expected = "Call=[name=[Ident[puts]],args=[Args[size=3,arg0=[IntLiteral=[1]],arg1=[IntLiteral=[2]],arg2=[IntLiteral=[3]]]]]\n";
    s_assert_cmpstr(call.to_string(), expected);
}
