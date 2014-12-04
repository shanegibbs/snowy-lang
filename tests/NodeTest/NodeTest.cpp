#include <glib.h>
#include <string>
#include <sstream>

#include <Nodes/Type.h>
#include <Nodes/Ident.h>
#include <Nodes/IntLiteral.h>
#include <Nodes/Operator.h>
#include <Nodes/Tuple.h>
#include <Nodes/DeclareVar.h>

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

    const char* actual = aDecl.to_program_string();
    g_assert_nonnull(actual);
    g_assert_cmpuint(strlen(actual), >, 0);
    g_assert_cmpstr(actual, ==, expected.c_str());
}
