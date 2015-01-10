#include <Engine.h>

#include "SnowyTestSuite.h"

void nodes_tests(Snowy::TestSuite&);
void parser_tests(Snowy::TestSuite&);
void it_tests(Snowy::TestSuite&);

int main()
{
    Snowy::Engine::init();

    Snowy::TestSuite tests;
    tests.add(nodes_tests);
    tests.add(parser_tests);
    tests.add(it_tests);
    return tests.run();
}
