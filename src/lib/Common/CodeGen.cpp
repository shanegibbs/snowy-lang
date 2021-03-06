#include <Log.h>

#include "CodeGen.h"

using namespace llvm;

namespace Snowy {

const Log CodeGen::log = Log("CodeGen");

CodeGen::CodeGen(IRBuilder<> *b, Module *m) {
  stringLiteralIndex = 0;
  builder = b;
  module = m;
}

void CodeGen::registerFunction(Function *fn) {
  log.debug("Registering function '%s'", fn->getName().data());
  functions[fn->getName()] = fn;
}

void CodeGen::registerValue(const string name, Value *value) {
  log.debug("Registering value '%s'", name.c_str());
  values[name] = value;
}

const Value *CodeGen::getValue(const string name) const {
  try {
    return values.at(name);
  } catch (std::out_of_range e) {
    log.fatal("Value '%s' not found", name.c_str());
    return NULL;
  }
}
}
