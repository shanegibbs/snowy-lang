#include <Log.h>

#include "CodeGen.h"

using namespace llvm;

namespace Snowy
{

const Log CodeGen::log = Log("CodeGen");

CodeGen::CodeGen(IRBuilder<>* b, Module* m)
{
    builder = b;
    module = m;
}

void CodeGen::registerFunction(Function* fn)
{
    log.debug("Registering function '%s'", fn->getName());
    functions[fn->getName()] = fn;
}

}
