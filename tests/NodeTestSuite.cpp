#include "SnowyTestSuite.h"

// IntLiteralTest
void int_literal_test(void);
void int_literal_multi_test(void);

// StringLiteralTest
void string_literal_to_string(void);

// CallTest
void call_no_arg_test(void);
void call_single_arg_test(void);
void call_three_arg_test(void);

// NodeTest
void node_basic_multi_test(void);

int main(int argc, char** argv)
{
    Snowy::TestSuite tests;
    tests.add("/Nodes/IntLiteral/test", int_literal_test);
    tests.add("/Nodes/IntLiteral/multi", int_literal_multi_test);
    tests.add("/Nodes/StringLiteral/to_string", string_literal_to_string);
    tests.add("/Nodes/Call/no_arg", call_no_arg_test);
    tests.add("/Nodes/Call/single_arg", call_single_arg_test);
    tests.add("/Nodes/Call/three_arg", call_three_arg_test);
    tests.add("/Nodes/Node/basic_multi_expr", node_basic_multi_test);
    return tests.run();
}
