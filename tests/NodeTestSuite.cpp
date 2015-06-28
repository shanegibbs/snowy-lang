#include <memory>

#include <IntLiteral.h>
#include <DeclareVar.h>
#include <FuncDef.h>
#include <DeclareClass.h>
#include <Ident.h>
#include <ArgsDecl.h>

#include "SnowyTestSuite.h"

using namespace std;
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
    FuncDef root(new Ident(strptr("myfunc")), new ArgsDecl(), NULL);

    std::ostringstream ss;
    ss << "FuncDef=[ident=[Ident[myfunc]] args=[ArgsDecl[size=0]] block=[NULL]]\n";
    const string expected = ss.str();

    const string& actual = root.to_program_string();
    s_assert_cmpint(actual.length(), >, 0);
    s_assert_cmpstr(actual, expected.c_str());
}

void node_declare_func_complex(void)
{
    IntLiteral* a = new IntLiteral(strptr("1"));
    IntLiteral* b = new IntLiteral(strptr("2"));
    IntLiteral* c = new IntLiteral(strptr("3"));
    a->setNext(b);
    b->setNext(c);

    FuncDef root(new Ident(strptr("myfunc")),
                     new ArgsDecl(new Ident(strptr("a")))
                     , a);

    std::ostringstream ss;
    ss << "FuncDef=[ident=[Ident[myfunc]] args=[ArgsDecl[size=1 arg0=[Ident[a]]]] block=[\n";
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
    DeclareClass root(new Type(strptr("MyClass")));

    std::ostringstream ss;
    ss << "DeclareClass=[type=[Type[MyClass]]]\n";
    const string expected = ss.str();

    const string& actual = root.to_program_string();
    s_assert_cmpint(actual.length(), >, 0);
    s_assert_cmpstr(actual, expected.c_str());
}

void node_declare_class_with_var(void)
{
    Type *type = new Type(strptr("MyClass"));
    DeclareClass root(type);
    root.addVarDecl(new DeclareVar(new Ident(strptr("i")), new IntLiteral(strptr("1"))));

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
    tests.add("/Nodes/FuncDef/simple", node_declare_func_simple);
    tests.add("/Nodes/FuncDef/complex", node_declare_func_complex);
    tests.add("/Nodes/DeclareClass/simple", node_declare_class_simple);
    tests.add("/Nodes/DeclareClass/with_var", node_declare_class_with_var);
}
