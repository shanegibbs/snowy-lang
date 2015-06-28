#include <stdio.h>
#include <string.h>

#include <SnowyAssert.h>

#include <Nodes/Call.h>
#include <Nodes/IntLiteral.h>
#include <Nodes/Ident.h>
#include <Nodes/DeclareFunc.h>
#include <Nodes/Args.h>
#include <Nodes/ArgsDecl.h>

#include "SnowyTestSuite.h"

using namespace Snowy;
using namespace std;

void call_no_arg_test(void)
{
    ArgsDecl *args_decl = new ArgsDecl();
    DeclareFunc *func = new DeclareFunc(new Ident(strptr("puts")), args_decl, nullptr);
    Call call(func, new Args());

    const char* expected = "Call=[name=[DeclareFunc=[ident=[Ident[puts]] args=[ArgsDecl[size=0]] block=[NULL]]],args=[Args[size=0]]]\n";
    const char* actual = call.to_string();
    s_assert_cmpstr(actual, expected);
    delete[] actual;
}

void call_single_arg_test(void)
{
    ArgsDecl *args_decl = new ArgsDecl();
    DeclareFunc *func = new DeclareFunc(new Ident(strptr("puts")), args_decl, nullptr);

    Call call(func, new Args(new IntLiteral(strptr(("5")))));

    const char* expected = "Call=[name=[DeclareFunc=[ident=[Ident[puts]] args=[ArgsDecl[size=0]] block=[NULL]]],args=[Args[size=1,arg0=[IntLiteral=[5]]]]]\n";
    const char* actual = call.to_string();
    s_assert_cmpstr(actual, expected);
    delete[] actual;
}

void call_three_arg_test(void)
{
    ArgsDecl *args_decl = new ArgsDecl();
    DeclareFunc *func = new DeclareFunc(new Ident(strptr("puts")), args_decl, nullptr);

    Args* args = new Args(new IntLiteral(strptr("1")));
    args->addArg(new IntLiteral(strptr("2")));
    args->addArg(new IntLiteral(strptr("3")));
    Call call(func, args);

    const char* expected = "Call=[name=[DeclareFunc=[ident=[Ident[puts]] args=[ArgsDecl[size=0]] block=[NULL]]],args=[Args[size=3,arg0=[IntLiteral=[1]],arg1=[IntLiteral=[2]],arg2=[IntLiteral=[3]]]]]\n";
    const char* actual = call.to_string();
    s_assert_cmpstr(actual, expected);
    delete[] actual;
}
