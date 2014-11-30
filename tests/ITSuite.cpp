#include <glib.h>
#include <stdlib.h>
#include <stdio.h>

#include <Engine.h>

using namespace Snowy;

void it_puts_string_lit_test()
{
    const unsigned int buf_size = 4096;
    char* buf = (char*)malloc(buf_size);

    Engine engine;
    engine.parse("puts \"hello world!!\"");

    engine.setStdoutBuffer(buf, buf_size);
    engine.exec();

    g_assert_cmpstr(buf, ==, "abc");
}

int main(int argc, char** argv)
{
    Log::setup();
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/IT/puts/StringLiteral", it_puts_string_lit_test);
    return g_test_run();
}

