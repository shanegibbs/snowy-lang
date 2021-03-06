#ifndef SNOWY_COMMON_CODEGEN_H
#define SNOWY_COMMON_CODEGEN_H

#include <map>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>

#include "SnowyAssert.h"

using namespace std;
using namespace llvm;

namespace Snowy {

class Log;

class CodeGen {
 public:
  CodeGen(IRBuilder<> *, Module *);
  void registerFunction(Function *fn);

  IRBuilder<> *getBuilder() const { return builder; }

  LLVMContext *getContext() const { return &builder->getContext(); }

  Module *getModule() const { return module; }

  unsigned int getNextStringLiteralIndex() { return stringLiteralIndex++; }

  void setCurrentFunc(Function *f) { currentFunc = f; }

  Function *getCurrentFunc() const { return currentFunc; };

  void registerValue(const string name, Value *value);
  const Value *getValue(const string) const;

 private:
  static const Log log;
  unsigned int stringLiteralIndex;
  IRBuilder<> *builder;
  Module *module;
  map<string, Function *> functions;
  map<string, Value *> values;

  Function *currentFunc;
};
}
#endif
