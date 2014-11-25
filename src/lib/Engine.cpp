#include <stdio.h>

#include <Parser.h>

#include "Engine.h"

namespace Snowy
{

int Engine::Parse()
{
    Parser *parser = new Parser;
    Snowy::Node *n = parser->parse();
    if (n != NULL) {
        puts("Program:");
        puts(n->to_program_string());
        return 0;
    } else {
        fprintf(stderr, "Parser->parse() returned NULL\n");
        return 1;
    }
}

Engine::Engine()
{
    puts("new Engine");
}

}
