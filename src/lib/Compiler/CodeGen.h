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
    IRBuilder<>* getBuilder() const
    {
        return builder;
    }
    void registerFunction(Function* fn);

    LLVMContext* getContext() const
    {
        return &builder->getContext();
    }

    Module* getModule() const
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
