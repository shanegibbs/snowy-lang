#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Argument.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "FuncDecl.h"
#include "Type.h"
#include "ArgsDecl.h"
#include "Ident.h"

using namespace llvm;

namespace Snowy {

  const Log FuncDecl::log = Log("FuncDecl");

  FuncDecl::FuncDecl(const Ident *i, const ArgsDecl *a) : ident(i), args(a) {
    s_assert_notnull(i);
    s_assert_notnull(a);
    log.debug("Creating FuncDecl node %s", ident->getName()->c_str());
  }

  FuncDecl::~FuncDecl() {
    delete ident;
    delete args;
  }

  FuncDecl *FuncDecl::clone() const {
    return new FuncDecl(*this);
  }

  const string &FuncDecl::getName() const {
    return *ident->getName();
  }

  const TypePtr FuncDecl::getType() const {
    return ident->getType();
  }

  void FuncDecl::to_sstream(std::ostringstream &s) const {
    s << "FuncDecl=[ident=[";
    ident->to_sstream(s);
    s << "] args=[";
    args->to_sstream(s);
    s << "]]";
  }

  Value *FuncDecl::compile(CodeGen &gen) const {
    log.debug("Compiling function def '%s'", ident->getName()->c_str());
    return nullptr;
  }

}
