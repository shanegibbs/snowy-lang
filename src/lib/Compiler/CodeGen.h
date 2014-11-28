#include <map>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

using namespace std;
using namespace llvm;

namespace Snowy
{

class Log;

class CodeGen
{
public:
    CodeGen(IRBuilder<>*, Module*);
    IRBuilder<>* getBuilder()
    {
        return builder;
    }
    void registerFunction(Function* fn);

    Module* getModule()
    {
        return module;
    }

private:
    static const Log log;
    IRBuilder<>* builder;
    Module* module;
    map<string, Function*> functions;
};

}
