#include <string.h>
#include <sstream>

#include <SnowyAssert.h>

#include <Type.h>
#include <Ident.h>
#include <IntLiteral.h>
#include <Operator.h>
#include <Tuple.h>
#include <DeclareVar.h>

using namespace Snowy;
using namespace std;

void node_basic_multi_test(void)
{
    Type type("int");

    Tuple* one_plus_two = new Tuple(
        new IntLiteral("1"),
        new Operator("+"),
        new IntLiteral("2"));
    DeclareVar root(
        new Type("int"),
        new Ident("a"),
        one_plus_two);

    Tuple* four_plus_five = new Tuple(
        new IntLiteral("4"),
        new Operator("+"),
        new IntLiteral("5"));
    DeclareVar* bDecl = new DeclareVar(
        new Type("int"),
        new Ident("b"),
        four_plus_five);
    root.setNext(bDecl);

    Tuple* ten_plus_eleven = new Tuple(
        new IntLiteral("10"),
        new Operator("+"),
        new IntLiteral("11"));
    DeclareVar* cDecl = new DeclareVar(
        new Type(new string("int")),
        new Ident(new string("c")),
        ten_plus_eleven);
    bDecl->setNext(cDecl);

    std::ostringstream ss;
    ss << "DeclareVar=[type=[Type[int]] ident=[Ident[a]] expr=[Tuple=[lhs=[IntLiteral=[1]] op=[+] rhs=[IntLiteral=[2]]]]]\n";
    ss << "DeclareVar=[type=[Type[int]] ident=[Ident[b]] expr=[Tuple=[lhs=[IntLiteral=[4]] op=[+] rhs=[IntLiteral=[5]]]]]\n";
    ss << "DeclareVar=[type=[Type[int]] ident=[Ident[c]] expr=[Tuple=[lhs=[IntLiteral=[10]] op=[+] rhs=[IntLiteral=[11]]]]]\n";
    const string expected = ss.str();

    const string& actual = root.to_program_string();
    s_assert_cmpint(actual.length(), >, 0);
    s_assert_cmpstr(actual, expected.c_str());
}
