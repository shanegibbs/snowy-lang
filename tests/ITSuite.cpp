#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

#include <Engine.h>

using namespace Snowy;

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
    const unsigned int buf_size = 4096;
    char* buf = (char*)malloc(buf_size);

    Engine engine;
    engine.parse("puts \"hello world!!\"\n");

    engine.setStdoutBuffer(buf, buf_size);
    engine.exec();

    g_assert_cmpstr(buf, ==, "hello world!!\n");
}

int main(int argc, char** argv)
{
    Log::setup();
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/IT/puts/stdout", it_puts_stdout_test);
    g_test_add_func("/IT/puts/StringLiteral", it_puts_string_lit_test);
    return g_test_run();
}
