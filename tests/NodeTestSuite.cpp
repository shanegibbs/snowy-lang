#include <IntLiteral.h>
#include <DeclareVar.h>
#include <DeclareFunc.h>
#include <DeclareClass.h>
#include <Ident.h>
#include <ArgsDecl.h>

#include "SnowyTestSuite.h"

using namespace Snowy;

// IntLiteralTest
void node_int_literal_tests(TestSuite&);

// StringLiteralTest
void string_literal_to_string(void);

// CallTest
void call_no_arg_test(void);
void call_single_arg_test(void);
void call_three_arg_test(void);

// NodeTest
void node_basic_multi_test(void);

void node_declare_func_simple(void)
{
    DeclareFunc root(new Ident("myfunc"), new ArgsDecl(), NULL);

    std::ostringstream ss;
    ss << "DeclareFunc=[ident=[Ident[myfunc]] args=[ArgsDecl[size=0]] block=[NULL]]\n";
    const string expected = ss.str();

    const string& actual = root.to_program_string();
    s_assert_cmpint(actual.length(), >, 0);
    s_assert_cmpstr(actual, expected.c_str());
}

void node_declare_func_complex(void)
{
    IntLiteral* a = new IntLiteral("1");
    IntLiteral* b = new IntLiteral("2");
    IntLiteral* c = new IntLiteral("3");
    a->setNext(b);
    b->setNext(c);

    DeclareFunc root(new Ident("myfunc"),
                     new ArgsDecl(new Ident("a"))
                     , a);

    std::ostringstream ss;
    ss << "DeclareFunc=[ident=[Ident[myfunc]] args=[ArgsDecl[size=1 arg0=[Ident[a]]]] block=[\n";
    ss << " IntLiteral=[1]\n";
    ss << " IntLiteral=[2]\n";
    ss << " IntLiteral=[3]\n";
    ss << "]]\n";
    const string expected = ss.str();

    const string& actual = root.to_program_string();
    s_assert_cmpint(actual.length(), >, 0);
    s_assert_cmpstr(actual, expected.c_str());
}

void node_declare_class_simple(void)
{
    DeclareClass root(new Type("MyClass"));

    std::ostringstream ss;
    ss << "DeclareClass=[type=[Type[MyClass]]]\n";
    const string expected = ss.str();

    const string& actual = root.to_program_string();
    s_assert_cmpint(actual.length(), >, 0);
    s_assert_cmpstr(actual, expected.c_str());
}

void node_declare_class_with_var(void)
{
    DeclareVar var = DeclareVar(new Ident("i"), new IntLiteral("1"));

    DeclareClass root(new Type("MyClass"));
    root.addVarDecl(&var);

    std::ostringstream ss;
    ss << "DeclareClass=[type=[Type[MyClass]]]\n";
    const string expected = ss.str();

    const string& actual = root.to_program_string();
    s_assert_cmpint(actual.length(), >, 0);
    s_assert_cmpstr(actual, expected.c_str());
}

void nodes_tests(TestSuite& tests)
{
    tests.add(node_int_literal_tests);
    tests.add("/Nodes/StringLiteral/to_string", string_literal_to_string);
    tests.add("/Nodes/Call/no_arg", call_no_arg_test);
    tests.add("/Nodes/Call/single_arg", call_single_arg_test);
    tests.add("/Nodes/Call/three_arg", call_three_arg_test);
    tests.add("/Nodes/Node/basic_multi_expr", node_basic_multi_test);
    tests.add("/Nodes/DeclareFunc/simple", node_declare_func_simple);
    tests.add("/Nodes/DeclareFunc/complex", node_declare_func_complex);
    tests.add("/Nodes/DeclareClass/simple", node_declare_class_simple);
    tests.add("/Nodes/DeclareClass/with_var", node_declare_class_with_var);
}
