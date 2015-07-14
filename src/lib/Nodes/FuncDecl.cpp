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

FuncDecl::FuncDecl(const Ident *i, const ArgsDecl *a, const bool vararg)
    : Callable(i, a, vararg) {
  log.debug("Creating FuncDecl node %s", ident->getName()->c_str());
}

FuncDecl *FuncDecl::clone() const { return new FuncDecl(*this); }

void FuncDecl::to_sstream(std::ostringstream &s) const {
  s << "FuncDecl=[ident=[";
  ident->to_sstream(s);
  s << "] args=[";
  args->to_sstream(s);
  s << "]";
  if (vararg) {
    s << " vararg=true";
  }
  s << "]";
}

Value *FuncDecl::compile(CodeGen &gen) const {
  log.debug("Compiling function def '%s'", ident->getName()->c_str());

  LLVMContext *context = &gen.getBuilder()->getContext();
  // BasicBlock* last_block = gen.getBuilder()->GetInsertBlock();
  // gen.getBuilder()->SetInsertPoint(gen.getDefInsertPoint());

  vector<llvm::Type *> ft_args = vector<llvm::Type *>();

  for (unsigned int i = 0; i < args->size(); i++) {
    const Ident &a = args->getIdent(i);
    llvm::Type *t = nullptr;

    if (a.getType()->getId() == "int") {
      t = llvm::Type::getInt32Ty(*context);
    } else if (a.getType()->getId() == "String") {
      t = llvm::Type::getInt8PtrTy(*context);
    } else {
      log.fatal("Type not found: %s", a.getType()->getId().c_str());
    }

    ft_args.push_back(t);
  }

  llvm::Type *t = nullptr;

  // printf("type is %s\n", ident->getType()->getId().c_str());
  if (ident->getType()->getId() == "int") {
    t = llvm::Type::getInt32Ty(*context);
  } else if (ident->getType()->getId() == "String") {
    t = llvm::Type::getInt8PtrTy(*context);
  }

  s_assert_notnull(t);
  FunctionType *ft = FunctionType::get(t, ft_args, vararg);

  Function *fn = Function::Create(ft, Function::ExternalLinkage,
                                  *ident->getName(), gen.getModule());

  gen.registerFunction(fn);

  // gen.getBuilder()->SetInsertPoint(last_block);
  return fn;
}
}
