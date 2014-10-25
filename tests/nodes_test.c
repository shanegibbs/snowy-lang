#include <glib.h>
#include <stdio.h>
#include <glib/gstdio.h>

#include "nodes.h"

void assert_code_desc(const char *code, const char *desc)
{
    opal_parse_string(code);
    g_assert_nonnull(root);
    g_assert_cmpstr(get_prog_desc(root), ==, desc);
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

int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/nodes/int_literal", int_literal_test);
    g_test_add_func("/nodes/multi_node", multi_node_test);
    g_test_add_func("/nodes/arithmetic_expr_test", arithmetic_expr_test);
    return g_test_run();
}
