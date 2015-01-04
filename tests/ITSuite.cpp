#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

#include <Engine.h>
#include <Log.h>
#include <SnowyAssert.h>

using namespace Snowy;

class Result
{
public:
    Result() {
        buffer = NULL;
        exit_code = 0;
    }
    char* buffer;
    int exit_code;
};

Result snowy_result(const char* code)
{
    Result result;

    const unsigned int buf_size = 4096;
    result.buffer = (char*)malloc(buf_size);

    Engine engine;
    engine.parse(code);

    engine.setStdoutBuffer(result.buffer, buf_size);
    result.exit_code = engine.exec();

    return result;
}

Result snowy_result_no_stdout(const char* code)
{
    Result result;

    Engine engine;
    engine.parse(code);

    result.exit_code = engine.exec();

    return result;
}

void it_puts_stdout_test()
{
    Engine engine;
    engine.parse("puts(\"hello world!!\")");

    if (g_test_subprocess()) {
        engine.exec();
        return;
    }

    g_test_trap_subprocess("/IT/puts/stdout", 0, G_TEST_SUBPROCESS_INHERIT_STDIN);
    g_test_trap_assert_stdout("hello world!!\n");
}

void it_puts_string_lit_test()
{
    Result actual = snowy_result("puts(\"hello world!!\")");
    g_assert_cmpstr(actual.buffer, ==, "hello world!!\n");
}

void it_puts_int_lit_test()
{
    Result actual = snowy_result("puts 5\n");
    g_assert_cmpstr(actual.buffer, ==, "5\n");
}

void it_return_int_test()
{
    Result actual = snowy_result_no_stdout("5\n");
    g_assert_cmpint(actual.exit_code, ==, 5);
}

void it_variable_use_1()
{
    Result actual = snowy_result("string a = \"one\"\nputs(a)");
    s_assert_cmpstr(actual.buffer, "one\n");
}

void it_variable_use_2()
{
    Result actual = snowy_result("string a = \"one\"\nstring b = \"two\"\nputs(a)");
    s_assert_cmpstr(actual.buffer, "one\n");
}

void it_add_int_single()
{
    Result actual = snowy_result_no_stdout("2 + 8\n");
    s_assert_cmpint(actual.exit_code, ==, 2 + 8);
}

void it_add_int_multi()
{
    Result actual = snowy_result_no_stdout("2 + 8 + 3 + 7\n");
    s_assert_cmpint(actual.exit_code, ==, 2 + 8 + 3 + 7);
}

void it_sub_int_single()
{
    Result actual = snowy_result_no_stdout("10 - 2\n");
    s_assert_cmpint(actual.exit_code, ==, 10 - 2);
}

void it_sub_int_multi()
{
    Result actual = snowy_result_no_stdout("20 - 12 - 5\n");
    s_assert_cmpint(actual.exit_code, ==, 20 - 12 - 5);
}

void it_mul_int_single()
{
    Result actual = snowy_result_no_stdout("10 * 2\n");
    s_assert_cmpint(actual.exit_code, ==, 10 * 2);
}

void it_mul_int_multi()
{
    Result actual = snowy_result_no_stdout("20 * 12 * 5\n");
    s_assert_cmpint(actual.exit_code, ==, 20 * 12 * 5);
}

void it_div_int_single()
{
    Result actual = snowy_result_no_stdout("10 / 2\n");
    s_assert_cmpint(actual.exit_code, ==, 10 / 2);
}

void it_div_int_multi()
{
    Result actual = snowy_result_no_stdout("20 / 4 / 2\n");
    s_assert_cmpint(actual.exit_code, ==, 20 / 4 / 2);
}

void it_brackets_int_left()
{
    Result actual = snowy_result_no_stdout("(10 - 5) + 2\n");
    s_assert_cmpint(actual.exit_code, ==, (10 - 5) + 2);
}

void it_brackets_int_right()
{
    Result actual = snowy_result_no_stdout("10 - (5 + 2)\n");
    s_assert_cmpint(actual.exit_code, ==, 10 - (5 + 2));
}

void it_function_declare_and_call_no_args()
{
    Result actual = snowy_result_no_stdout("int myval() do\n8\nend\nmyval()\n");
    s_assert_cmpint(actual.exit_code, ==, 8);
}

void it_function_declare_and_call()
{
    Result actual = snowy_result_no_stdout("int add(int a, int b) do\na + b\nend\nadd(1, 3)\n");
    s_assert_cmpint(actual.exit_code, ==, 3);
}

int main(int argc, char** argv)
{
    Log::setup();
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/IT/puts/stdout", it_puts_stdout_test);
    g_test_add_func("/IT/puts/StringLiteral", it_puts_string_lit_test);
    // g_test_add_func("/IT/puts/IntLiteral", it_puts_int_lit_test);
    g_test_add_func("/IT/return/Int", it_return_int_test);
    g_test_add_func("/IT/variable/use/1", it_variable_use_1);
    g_test_add_func("/IT/variable/use/2", it_variable_use_2);
    g_test_add_func("/IT/add/int/single", it_add_int_single);
    g_test_add_func("/IT/add/int/multi", it_add_int_multi);
    g_test_add_func("/IT/sub/int/single", it_sub_int_single);
    g_test_add_func("/IT/sub/int/multi", it_sub_int_multi);
    g_test_add_func("/IT/mul/int/single", it_mul_int_single);
    g_test_add_func("/IT/mul/int/multi", it_mul_int_multi);
    g_test_add_func("/IT/div/int/single", it_div_int_single);
    g_test_add_func("/IT/div/int/multi", it_div_int_multi);
    g_test_add_func("/IT/brackets/int/left", it_brackets_int_left);
    g_test_add_func("/IT/brackets/int/right", it_brackets_int_right);
    g_test_add_func("/IT/function/declare_and_call_no_args", it_function_declare_and_call_no_args);
    // g_test_add_func("/IT/function/declare_and_call", it_function_declare_and_call);
    return g_test_run();
}
