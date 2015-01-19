#include <stdio.h>

#include <Parser.h>
#include <Node.h>
#include <DeclareClass.h>
#include <DeclareVar.h>
#include <DeclareFunc.h>

#include "SnowyTestSuite.h"

using namespace Snowy;

static const Node& build_graph(string code)
{
    std::stringstream ins;
    ins << code;

    Parser parser;
    Node *root = parser.parse(ins);
    s_assert_notnull(root);
    return *root;
}

static void assert_code_desc(const char *code, const string& expected)
{
    std::stringstream ins;
    ins << code;

    Parser parser;
    Node *root = parser.parse(ins);
    s_assert_notnull(root);

    const string& actual = root->to_program_string();
    delete root;
    s_assert_cmpstr(actual, expected);
}

void string_literal_test(void)
{
    assert_code_desc("\"abc\"\n", "StringLiteral=[\"abc\"]\n");
}

void int_literal_test(void)
{
    assert_code_desc("1\n", "IntLiteral=[1]\n");
}

void multi_node_test(void)
{
    assert_code_desc("1\n2\n3\n", "IntLiteral=[1]\nIntLiteral=[2]\nIntLiteral=[3]\n");
}

void arithmetic_expr_test(void)
{
    const char *code = "1 + 2\n";
    const char *desc = "Tuple=[lhs=[IntLiteral=[1]] op=[+] rhs=[IntLiteral=[2]]]\n";
    assert_code_desc(code, desc);
}

void assignment_test(void)
{
    const char *code = "int a = 1 + 2\n";
    const char *desc = "DeclareVar=[type=[Type[int]] ident=[Ident[a]] expr=[Tuple=[lhs=[IntLiteral=[1]] op=[+] rhs=[IntLiteral=[2]]]]]\n";
    assert_code_desc(code, desc);
}

void string_assignment_test(void)
{
    const char *code = "String a = \"this is a test\"\n";
    const char *desc = "DeclareVar=[type=[Type[String]] ident=[Ident[a]] expr=[StringLiteral=[\"this is a test\"]]]\n";
    assert_code_desc(code, desc);
}

void multi_assignment_test(void)
{
    // TODO
}

void func_no_args(void)
{
    const char *code = "int add() do\nend\n";
    const char *desc = "DeclareFunc=[type=[Type[int]] ident=[Ident[add]] args=[ArgsDecl[size=0]] block=[NULL]]\n";
    assert_code_desc(code, desc);
}

void func_one_arg(void)
{
    const char *code = "int add(int one) do\nend\n";
    const char *desc = "DeclareFunc=[type=[Type[int]] ident=[Ident[add]] args=[ArgsDecl[size=1 type0=[Type[int]] ident0=[Ident[one]]]] block=[NULL]]\n";
    assert_code_desc(code, desc);
}

void func_two_args(void)
{
    const char *code = "int add(int one, String two) do\nend\n";
    const char *desc = "DeclareFunc=[type=[Type[int]] ident=[Ident[add]] args=[ArgsDecl[size=2 type0=[Type[int]] ident0=[Ident[one]] type1=[Type[String]] ident1=[Ident[two]]]] block=[NULL]]\n";
    assert_code_desc(code, desc);
}

void func_body_one_line(void)
{
    const char *code = "int test() do\n1\nend\n";
    const char *desc = "DeclareFunc=[type=[Type[int]] ident=[Ident[test]] args=[ArgsDecl[size=0]] block=[\n IntLiteral=[1]\n]]\n";
    assert_code_desc(code, desc);
}

void func_body_multi_line(void)
{
    const char *code = "int test() do\n1\n2\n3\nend\n";
    const char *desc = "DeclareFunc=[type=[Type[int]] ident=[Ident[test]] args=[ArgsDecl[size=0]] block=[\n IntLiteral=[1]\n IntLiteral=[2]\n IntLiteral=[3]\n]]\n";
    assert_code_desc(code, desc);
}

static void empty_line_test(void)
{
    assert_code_desc(R"snow(

        1
    )snow", "IntLiteral=[1]\n");
}

static void comment_full_line_test(void)
{
    assert_code_desc(R"snow(
        # 1
        1
    )snow", "IntLiteral=[1]\n");
}

static void comment_part_line_test(void)
{
    assert_code_desc(R"snow(
        1 # 2
    )snow", "IntLiteral=[1]\n");
}

static void class_declare_empty(void)
{
    assert_code_desc(R"snow(
        class MyClass do
        end
    )snow", "DeclareClass=[ident=[Ident[MyClass]]]\n");
}

static void class_declare_with_var(void)
{
    const Node& n = build_graph(R"snow(
        class MyClass do
          int i = 0
        end
    )snow");

    s_assert(n.isNodeType(DECLARE_CLASS));
    DeclareClass& c = (DeclareClass&)n;

    s_assert_cmpstr(*c.getIdent().getName(), "MyClass");
    s_assert(c.getVars().size() == 1);

    DeclareVar& var = *c.getVars()[0];
    s_assert_cmpstr(var.to_program_string(), "DeclareVar=[type=[Type[int]] ident=[Ident[i]] expr=[IntLiteral=[0]]]\n");
}

static void class_declare_with_var_no_spaces(void)
{
    const Node& n = build_graph("class MyClass do\nint i = 0\nend\n");

    s_assert(n.isNodeType(DECLARE_CLASS));
    DeclareClass& c = (DeclareClass&)n;

    s_assert_cmpstr(*c.getIdent().getName(), "MyClass");
    s_assert(c.getVars().size() == 1);

    DeclareVar& var = *c.getVars()[0];
    s_assert_cmpstr(var.to_program_string(), "DeclareVar=[type=[Type[int]] ident=[Ident[i]] expr=[IntLiteral=[0]]]\n");
}

static void class_declare_with_two_vars(void)
{
    const Node& n = build_graph(R"snow(
        class MyClass do
          int a = 0
          int b = 0
        end
    )snow");

    s_assert(n.isNodeType(DECLARE_CLASS));
    DeclareClass& c = (DeclareClass&)n;

    s_assert_cmpstr(*c.getIdent().getName(), "MyClass");
    s_assert(c.getVars().size() == 2);

    DeclareVar& a = *c.getVars()[0];
    s_assert_cmpstr(a.to_program_string(), "DeclareVar=[type=[Type[int]] ident=[Ident[a]] expr=[IntLiteral=[0]]]\n");

    DeclareVar& b = *c.getVars()[1];
    s_assert_cmpstr(b.to_program_string(), "DeclareVar=[type=[Type[int]] ident=[Ident[b]] expr=[IntLiteral=[0]]]\n");
}

static void class_declare_with_func(void)
{
    const Node& n = build_graph(R"snow(
        class MyClass do
          int myfunc() do
          end
        end
    )snow");

    s_assert(n.isNodeType(DECLARE_CLASS));
    DeclareClass& c = (DeclareClass&)n;

    s_assert_cmpstr(*c.getIdent().getName(), "MyClass");
    s_assert(c.getFuncs().size() == 1);

    DeclareFunc& func = *c.getFuncs()[0];
    s_assert_cmpstr(func.getName(), "myfunc");
}

static void class_declare_with_two_funcs(void)
{
    const Node& n = build_graph(R"snow(
        class MyClass do
          int firstFunc() do
            int a = 0
          end
          int secondFunc() do
            int b = 0
          end
        end
    )snow");

    s_assert(n.isNodeType(DECLARE_CLASS));
    DeclareClass& c = (DeclareClass&)n;

    s_assert_cmpstr(*c.getIdent().getName(), "MyClass");
    s_assert(c.getFuncs().size() == 2);

    DeclareFunc& first_func = *c.getFuncs()[0];
    s_assert_cmpstr(first_func.getName(), "firstFunc");

    DeclareFunc& second_func = *c.getFuncs()[1];
    s_assert_cmpstr(second_func.getName(), "secondFunc");
}

void parser_tests(TestSuite& tests)
{
    tests.add("/Parser/int_literal", int_literal_test);
    tests.add("/Parser/string_literal", string_literal_test);
    tests.add("/Parser/multi_node", multi_node_test);
    tests.add("/Parser/arithmetic_expr_test", arithmetic_expr_test);
    tests.add("/Parser/assignment_test", assignment_test);
    tests.add("/Parser/string_assignment_test", string_assignment_test);
    tests.add("/Parser/multi_assignment_test", multi_assignment_test);
    tests.add("/Parser/func/no_args", func_no_args);
    tests.add("/Parser/func/one_arg", func_one_arg);
    tests.add("/Parser/func/two_args", func_two_args);
    tests.add("/Parser/func/body_one_line", func_body_one_line);
    tests.add("/Parser/func/body_multi_line", func_body_multi_line);
    tests.add("/Parser/empty_line", empty_line_test);
    tests.add("/Parser/comment/full_line", comment_full_line_test);
    tests.add("/Parser/comment/part_line", comment_part_line_test);
    tests.add("/Parser/class/empty", class_declare_empty);
    tests.add("/Parser/class/with_var", class_declare_with_var);
    tests.add("/Parser/class/with_var_no_spaces", class_declare_with_var_no_spaces);
    tests.add("/Parser/class/with_two_vars", class_declare_with_two_vars);
    tests.add("/Parser/class/with_func", class_declare_with_func);
    tests.add("/Parser/class/with_two_funcs", class_declare_with_two_funcs);
}
