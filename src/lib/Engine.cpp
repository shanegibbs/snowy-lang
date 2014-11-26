#include <stdio.h>

#include <Parser.h>
#include <Compiler.h>

#include "Engine.h"

namespace Snowy
{

int Engine::Parse()
{
    Parser parser = Parser();
    Snowy::Node *n = parser.parse();
    if (n == NULL) {
        fprintf(stderr, "Parser->parse() returned NULL\n");
        return 1;
    }

    puts("Program:");
    puts(n->to_program_string());

    Compiler compiler;
    compiler.compile(n);

    return 0;
}

Engine::Engine()
{
    puts("new Engine");
}

}
