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
    CodeGen(IRBuilder<>*);
    IRBuilder<>* getBuilder()
    {
        return builder;
    }
    void registerFunction(Function* fn);

private:
    static const Log log;
    IRBuilder<>* builder;
    map<string, Function*> functions;
};

}
