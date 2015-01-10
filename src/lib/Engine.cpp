#include <stdio.h>
#include <stdlib.h>

#include <Log.h>
#include <SnowyAssert.h>
#include <Parser.h>
#include <Compiler.h>
#include <Execer.h>

#include "Engine.h"

using namespace std;
using namespace llvm;

namespace Snowy
{

const Log Engine::log = Log("Engine");

void Engine::shutdown()
{
    Execer::shutdown();
}

void Engine::init()
{
    atexit(Engine::shutdown);
}

Engine::Engine()
{
    log.debug("Creating Engine");
    parser = new Parser;
    compiler = new Compiler;
    execer = new Execer;
    module = NULL;
    buffer = NULL;
}

Engine::~Engine()
{
    log.debug("Destroy Engine");
    delete parser;
    delete compiler;
    delete execer;
}

void Engine::setStdoutBuffer(char* b, int s)
{
    log.debug("Setting stdout buffer");
    buffer = b;
    buffer_size = s;
}

bool Engine::parse()
{
    Node *n = parser->parse();
    if (n == NULL) {
        log.warn("Parser->parse() returned NULL");
        return false;
    }

    const string& program_str = n->to_program_string();
    log.info("Program:\n%s", program_str.c_str());

    module = compiler->compile(n);
    delete n;

    return true;
}

bool Engine::parse(string code)
{
    std::stringstream ins;
    ins << code;
    return parse(ins);
}

bool Engine::parse(istream& ins)
{
    Node* n = parser->parse(ins);
    if (n == NULL) {
        log.warn("Parser->parse() returned NULL");
        return false;
    }

    const string& program_str = n->to_program_string();
    log.info("Program:\n%s", program_str.c_str());

    module = compiler->compile(n);
    delete n;

    return true;
}

int Engine::exec()
{
    s_assert_notnull(module);
    if (buffer != NULL) {
        execer->setStdoutBuffer(buffer, buffer_size);
    }
    return execer->exec(module);
}

}
