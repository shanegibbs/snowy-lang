#include <glib.h>

// IntLiteralTest
void int_literal_test(void);
void int_literal_multi_test(void);

// StringLiteralTest
void string_literal_to_string(void);

// NodeTest
void node_basic_multi_test(void);

int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/Nodes/IntLiteral/test", int_literal_test);
    g_test_add_func("/Nodes/IntLiteral/multi", int_literal_multi_test);
    g_test_add_func("/Nodes/StringLiteral/to_string", string_literal_to_string);
    g_test_add_func("/Nodes/Node/basic_multi_expr", node_basic_multi_test);
    return g_test_run();
}
