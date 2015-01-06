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

    Ident a("a");
    IntLiteral one("1");
    IntLiteral two("2");
    Operator plus_a("+");
    Tuple one_plus_two(&one, &plus_a, &two);
    DeclareVar aDecl(&type, &a, &one_plus_two);

    Ident b("b");
    IntLiteral four("4");
    IntLiteral five("5");
    Operator plus_b("+");
    Tuple four_plus_five(&four, &plus_b, &five);
    DeclareVar bDecl(&type, &b, &four_plus_five);
    aDecl.setNext(&bDecl);

    Ident c("c");
    IntLiteral ten("10");
    IntLiteral eleven("11");
    Operator plus_c("+");
    Tuple ten_plus_eleven(&ten, &plus_c, &eleven);
    DeclareVar cDecl(&type, &c, &ten_plus_eleven);
    bDecl.setNext(&cDecl);

    std::ostringstream ss;
    ss << "DeclareVar=[type=[Type[int]] ident=[Ident[a]] expr=[Tuple=[lhs=[IntLiteral=[1]] op=[+] rhs=[IntLiteral=[2]]]]]\n";
    ss << "DeclareVar=[type=[Type[int]] ident=[Ident[b]] expr=[Tuple=[lhs=[IntLiteral=[4]] op=[+] rhs=[IntLiteral=[5]]]]]\n";
    ss << "DeclareVar=[type=[Type[int]] ident=[Ident[c]] expr=[Tuple=[lhs=[IntLiteral=[10]] op=[+] rhs=[IntLiteral=[11]]]]]\n";
    const string expected = ss.str();

    const string& actual = aDecl.to_program_string();
    s_assert_cmpint(actual.length(), >, 0);
    s_assert_cmpstr(actual, expected.c_str());
}
