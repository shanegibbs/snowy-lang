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

void nodes_tests(TestSuite& tests)
{
    tests.add(node_int_literal_tests);
    tests.add("/Nodes/StringLiteral/to_string", string_literal_to_string);
    tests.add("/Nodes/Call/no_arg", call_no_arg_test);
    tests.add("/Nodes/Call/single_arg", call_single_arg_test);
    tests.add("/Nodes/Call/three_arg", call_three_arg_test);
    tests.add("/Nodes/Node/basic_multi_expr", node_basic_multi_test);
}
