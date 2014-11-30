#include <Log.h>

#include "CodeGen.h"

using namespace llvm;

namespace Snowy
{

const Log CodeGen::log = Log("CodeGen");

CodeGen::CodeGen(IRBuilder<>* b, Module* m)
{
    stringLiteralIndex = 0;
    builder = b;
    module = m;
}

void CodeGen::registerFunction(Function* fn)
{
    log.debug("Registering function '%s'", fn->getName().data());
    functions[fn->getName()] = fn;
}

}
