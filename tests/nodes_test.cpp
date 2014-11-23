#include <glib.h>
#include <stdio.h>
#include <glib/gstdio.h>

#include <Parser/Driver.h>

void assert_code_desc(const char *code, const char *desc)
{
    Snowy::Driver *driver = new Snowy::Driver;
    Snowy::Node *root = driver->parse(code);
    g_assert_nonnull(root);

    const char* actual = root->to_program_string();
    g_assert_cmpstr(actual, ==, desc);
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
    const char *code = "a = 1 + 2\n";
    const char *desc = "DeclareVar=[ident=[Ident[a]] expr=[Tuple=[lhs=[IntLiteral=[1]] op=[+] rhs=[IntLiteral=[2]]]]]\n";
    assert_code_desc(code, desc);
}

int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/Parser/int_literal", int_literal_test);
    g_test_add_func("/Parser/multi_node", multi_node_test);
    g_test_add_func("/Parser/arithmetic_expr_test", arithmetic_expr_test);
    g_test_add_func("/Parser/assignment_test", assignment_test);
    return g_test_run();
}
