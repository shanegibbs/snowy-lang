#include <stdlib.h>
#include <stdio.h>

#include "SnowyTestSuite.h"
#include <Engine.h>

using namespace Snowy;

class Result {
 public:
  Result() {
    buffer = NULL;
    exit_code = 0;
  }
  ~Result() { free(buffer); }
  char *buffer;
  int exit_code;
};

Result snowy_result(const char *code) {
  Result result;

  const unsigned int buf_size = 4096;
  result.buffer = (char *)malloc(buf_size);

  Engine engine;
  engine.parse(code);

  engine.setStdoutBuffer(result.buffer, buf_size);
  result.exit_code = engine.exec();

  return result;
}

Result snowy_result_no_stdout(const char *code) {
  Result result = snowy_result(code);
  s_assert_cmpstr(result.buffer, "");
  return result;
}

/* TODO port stdout test
void it_puts_stdout_test()
{
    Engine engine;
    engine.parse("puts(\"hello world!!\")");

    if (g_test_subprocess()) {
        engine.exec();
        return;
    }

    g_test_trap_subprocess("/IT/puts/stdout", 0,
G_TEST_SUBPROCESS_INHERIT_STDIN);
    g_test_trap_assert_stdout("hello world!!\n");
}
*/

void it_puts_string_lit_test() {
  Result actual = snowy_result(R"snow(
        declare int:puts(String:s)
        puts("hello world!!")
    )snow");
  s_assert_cmpstr(actual.buffer, "hello world!!\n");
}

void it_puts_int_lit_test() {
  Result actual = snowy_result("puts 5\n");
  s_assert_cmpstr(actual.buffer, "5\n");
}

void it_return_int_test() {
  Result actual = snowy_result_no_stdout("5");
  s_assert_cmpint(actual.exit_code, ==, 5);
}

void it_variable_use_1() {
  Result actual = snowy_result(R"snow(
        declare int:puts(String:s)
        a = "one"
        puts(a)
    )snow");
  s_assert_cmpstr(actual.buffer, "one\n");
}

void it_variable_use_2() {
  Result actual = snowy_result(
      "declare int:puts(String:s)\na = \"one\"\nb = \"two\"\nputs(a)");
  s_assert_cmpstr(actual.buffer, "one\n");
}

void it_add_int_single() {
  Result actual = snowy_result_no_stdout("2 + 8");
  s_assert_cmpint(actual.exit_code, ==, 2 + 8);
}

void it_add_int_multi() {
  Result actual = snowy_result_no_stdout("2 + 8 + 3 + 7");
  s_assert_cmpint(actual.exit_code, ==, 2 + 8 + 3 + 7);
}

void it_sub_int_single() {
  Result actual = snowy_result_no_stdout("10 - 2");
  s_assert_cmpint(actual.exit_code, ==, 10 - 2);
}

void it_sub_int_multi() {
  Result actual = snowy_result_no_stdout("20 - 12 - 5");
  s_assert_cmpint(actual.exit_code, ==, 20 - 12 - 5);
}

void it_mul_int_single() {
  Result actual = snowy_result_no_stdout("10 * 2");
  s_assert_cmpint(actual.exit_code, ==, 10 * 2);
}

void it_mul_int_multi() {
  Result actual = snowy_result_no_stdout("20 * 12 * 5");
  s_assert_cmpint(actual.exit_code, ==, 20 * 12 * 5);
}

void it_div_int_single() {
  Result actual = snowy_result_no_stdout("10 / 2");
  s_assert_cmpint(actual.exit_code, ==, 10 / 2);
}

void it_div_int_multi() {
  Result actual = snowy_result_no_stdout("20 / 4 / 2");
  s_assert_cmpint(actual.exit_code, ==, 20 / 4 / 2);
}

void it_brackets_int_left() {
  Result actual = snowy_result_no_stdout("(10 - 5) + 2");
  s_assert_cmpint(actual.exit_code, ==, (10 - 5) + 2);
}

void it_brackets_int_right() {
  Result actual = snowy_result_no_stdout("10 - (5 + 2)");
  s_assert_cmpint(actual.exit_code, ==, 10 - (5 + 2));
}

void it_function_declare_and_call() {
  Result actual = snowy_result_no_stdout(R"snow(
        def myval() do
        end
        myval()
    )snow");
  s_assert_cmpint(actual.exit_code, ==, 0);
}

void it_function_declare_and_call_with_block() {
  Result actual = snowy_result(R"snow(
        declare int:puts(String:s)
        def myfunc() do
          puts("In myfunc")
          1
        end
        myfunc()
    )snow");
  s_assert_cmpstr(actual.buffer, "In myfunc\n");
  s_assert_cmpint(actual.exit_code, ==, 1);
}

void it_function_declare_and_call_with_args() {
  Result actual = snowy_result_no_stdout(R"snow(
        def add(a, b) do
          a + b
        end
        add(1, 3)
    )snow");
  s_assert_cmpint(actual.exit_code, ==, 4);
}

void it_class_declare_empty() {
  snowy_result_no_stdout(R"snow(
        class MyClass do
        end
    )snow");
}

void it_tests(Snowy::TestSuite &tests) {
  // tests.add("/IT/puts/stdout", it_puts_stdout_test);
  tests.add("/IT/puts/StringLiteral", it_puts_string_lit_test);
  // tests.add("/IT/puts/IntLiteral", it_puts_int_lit_test);
  tests.add("/IT/return/Int", it_return_int_test);
  tests.add("/IT/variable/use/1", it_variable_use_1);
  tests.add("/IT/variable/use/2", it_variable_use_2);
  tests.add("/IT/add/int/single", it_add_int_single);
  tests.add("/IT/add/int/multi", it_add_int_multi);
  tests.add("/IT/sub/int/single", it_sub_int_single);
  tests.add("/IT/sub/int/multi", it_sub_int_multi);
  tests.add("/IT/mul/int/single", it_mul_int_single);
  tests.add("/IT/mul/int/multi", it_mul_int_multi);
  tests.add("/IT/div/int/single", it_div_int_single);
  tests.add("/IT/div/int/multi", it_div_int_multi);
  tests.add("/IT/brackets/int/left", it_brackets_int_left);
  tests.add("/IT/brackets/int/right", it_brackets_int_right);
  tests.add("/IT/function/declare_and_call", it_function_declare_and_call);
  tests.add("/IT/function/declare_and_call_with_block",
            it_function_declare_and_call_with_block);
  tests.add("/IT/function/declare_and_call_with_args",
            it_function_declare_and_call_with_args);
  tests.add("/IT/class/declare/empty", it_class_declare_empty);
}
