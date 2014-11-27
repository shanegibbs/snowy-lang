#include <stdio.h>

#include <Parser.h>
#include <Compiler.h>

#include "Engine.h"

namespace Snowy
{

const Log Engine::log = Log("Engine");

Engine::Engine()
{
}

int Engine::Parse()
{
    Parser parser = Parser();
    Snowy::Node *n = parser.parse();
    if (n == NULL) {
        log.warn("Parser->parse() returned NULL");
        return 1;
    }

    log.info("Program:\n%s", n->to_program_string());

    Compiler compiler;
    compiler.compile(n);

    return 0;
}

}
