#ifndef SNOWY_ENGINE_H
#define SNOWY_ENGINE_H

#include <string>

#include <Log.h>

using namespace std;

namespace llvm
{
class Module;
}

namespace Snowy
{

class Parser;
class Compiler;
class Execer;

class Engine
{
public:
    Engine();
    ~Engine();

    bool parse();
    bool parse(string code);
    void setStdoutBuffer(char* buffer, int size);
    int exec();

private:
    static const Log log;
    char* buffer;
    unsigned int buffer_size;
    llvm::Module *module;
    Parser *parser;
    Compiler *compiler;
    Execer *execer;
};

}

#endif
