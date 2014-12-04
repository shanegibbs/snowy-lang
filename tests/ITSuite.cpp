#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

#include <Engine.h>
#include <Log.h>

using namespace Snowy;

class Result
{
public:
    Result()
    {
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
    engine.parse("puts \"hello world!!\"\n");

    if (g_test_subprocess()) {
        engine.exec();
        return;
    }

    g_test_trap_subprocess("/IT/puts/stdout", 0, G_TEST_SUBPROCESS_INHERIT_STDIN);
    g_test_trap_assert_stdout("hello world!!\n");
}

void it_puts_string_lit_test()
{
    Result actual = snowy_result("puts \"hello world!!\"\n");
    g_assert_cmpstr(actual.buffer, ==, "hello world!!\n");
}

void it_puts_int_lit_test()
{
    Result actual = snowy_result("puts 5\n");
    g_assert_cmpstr(actual.buffer, ==, "5\n");
}

void it_int_return_test()
{
    Result actual = snowy_result_no_stdout("5\n");
    g_assert_cmpint(actual.exit_code, ==, 5);
}

int main(int argc, char** argv)
{
    Log::setup();
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/IT/puts/stdout", it_puts_stdout_test);
    g_test_add_func("/IT/puts/StringLiteral", it_puts_string_lit_test);
    // g_test_add_func("/IT/puts/IntLiteral", it_puts_int_lit_test);
    g_test_add_func("/IT/return/Int", it_int_return_test);
    return g_test_run();
}
