#include <stdio.h>

#include <Parser.h>
#include <Compiler.h>
#include <Execer.h>

#include "Engine.h"

using namespace std;

namespace Snowy
{

const Log Engine::log = Log("Engine");

Engine::Engine()
{
    log.debug("Creating Engine");
}

Engine::~Engine()
{
    log.debug("Destroy Engine");
}

void Engine::setStdoutBuffer(char* b, int s)
{
    buffer = b;
    buffer_size = s;
}

int Engine::parse()
{
    Parser parser = Parser();
    Snowy::Node *n = parser.parse();
    if (n == NULL) {
        log.warn("Parser->parse() returned NULL");
        return 1;
    }

    log.info("Program:\n%s", n->to_program_string());

    Compiler compiler;
    llvm::Module* module = compiler.compile(n);

    Execer execer(module);
    return execer.exec();
}

int Engine::parse(string code)
{
    return 0;
}

}
