#include <Engine.h>

#include "SnowyTestSuite.h"

void nodes_tests(Snowy::TestSuite&);
void parser_tests(Snowy::TestSuite&);
void it_tests(Snowy::TestSuite&);

int main(int argc, char* const* argv)
{
    Snowy::Engine::init();

    Snowy::TestSuite tests;
    tests.add(nodes_tests);
    tests.add(parser_tests);
    tests.add(it_tests);

    if (argc == 2) {
        tests.setFilter(new string(argv[1]));
    }

    return tests.run();
}
