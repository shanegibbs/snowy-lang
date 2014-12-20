#include <glib.h>
#include <stdio.h>
#include <glib/gstdio.h>

#include <SnowyAssert.h>
#include <Parser.h>
#include <Node.h>

using namespace Snowy;

void assert_code_desc(const char *code, const char *expected)
{
    Parser *parser = new Parser;
    Node *root = parser->parse(code);
    s_assert_notnull(root);

    const char* actual = root->to_program_string();
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
    const char *desc = "DeclareFunc=[type=[Type[int]] ident=[Ident[test]] args=[ArgsDecl[size=0]] block=[IntLiteral=[1]]]\n";
    assert_code_desc(code, desc);
}

void func_body_multi_line(void)
{
    const char *code = "int test() do\n1\n2\n3\nend\n";
    const char *desc = "DeclareFunc=[type=[Type[int]] ident=[Ident[test]] args=[ArgsDecl[size=0]] block=[IntLiteral=[1] IntLiteral=[2]]]\n";
    assert_code_desc(code, desc);
}

int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/Parser/int_literal", int_literal_test);
    g_test_add_func("/Parser/string_literal", string_literal_test);
    g_test_add_func("/Parser/multi_node", multi_node_test);
    g_test_add_func("/Parser/arithmetic_expr_test", arithmetic_expr_test);
    g_test_add_func("/Parser/assignment_test", assignment_test);
    g_test_add_func("/Parser/string_assignment_test", string_assignment_test);
    g_test_add_func("/Parser/multi_assignment_test", multi_assignment_test);
    g_test_add_func("/Parser/func/no_args", func_no_args);
    g_test_add_func("/Parser/func/one_arg", func_one_arg);
    g_test_add_func("/Parser/func/two_args", func_two_args);
    // g_test_add_func("/Parser/func/body_one_line", func_body_one_line);
    // g_test_add_func("/Parser/func/body_multi_line", func_body_multi_line);
    return g_test_run();
}
