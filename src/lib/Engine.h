#ifndef SNOWY_ENGINE_H
#define SNOWY_ENGINE_H

#include <istream>
#include <string>

using namespace std;

namespace llvm
{
class Module;
}

namespace Snowy
{

class Log;
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
    bool parse(istream&);
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
