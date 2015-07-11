#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Support/TargetSelect.h>

#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Bitcode/ReaderWriter.h>

#include <Log.h>
#include <Call.h>

#include "CodeGen.h"
#include "Compiler.h"

using namespace std;
using namespace llvm;

namespace Snowy {

const Log Compiler::log = Log("Compiler");

Compiler::Compiler() { context = new LLVMContext(); }

Compiler::~Compiler() { delete context; }

Value *Compiler::get_exit_value(Value *last_val) {
  Value *zero = ConstantInt::get(*context, APInt(32, 0, false));

  if (last_val == NULL) {
    log.debug("Last value was NULL. Setting exit code to 0");
    return zero;
  }

  llvm::Type *retType = last_val->getType();

  if (retType->isIntegerTy(32)) {
    log.debug("Last value was i32. Setting exit code to last_val");
    return last_val;
  } else {
    log.debug("Last value was not i32. Setting exit code to 0");
    return ConstantInt::get(*context, APInt(32, 0, false));
  }
}

Module *Compiler::compile(Node *n) {
  log.info("Compiling");

  IRBuilder<> *builder = new IRBuilder<>(*context);

  Module *TheModule = new Module("org.default", *context);
  TheModule->setTargetTriple("x86_64-unknown-linux-gnu");

  CodeGen codeGen = CodeGen(builder, TheModule);

  // main
  std::vector<llvm::Type *> main_args;
  // int argc
  main_args.push_back(IntegerType::get(*context, 32));
  // char** argv
  PointerType *char_star_type =
      PointerType::get(IntegerType::get(*context, 8), 0);
  PointerType *char_star_arr_type = PointerType::get(char_star_type, 0);
  main_args.push_back(char_star_arr_type);
  // prototype
  FunctionType *main_ft =
      FunctionType::get(llvm::Type::getInt32Ty(*context), main_args, false);

  // function
  Function *main_fn =
      Function::Create(main_ft, Function::ExternalLinkage, "main", TheModule);
  Function::arg_iterator args = main_fn->arg_begin();
  Value *int32_ac = args++;
  int32_ac->setName("argc_val");
  Value *ptr_av = args++;
  ptr_av->setName("argv_val");

  BasicBlock *main_block = BasicBlock::Create(*context, "main_fn", main_fn);
  builder->SetInsertPoint(main_block);
  codeGen.setCurrentFunc(main_fn);

  llvm::Type *mem_type = int32_ac->getType();
  ConstantInt *mem_count = builder->getInt32(1);
  AllocaInst *mem = builder->CreateAlloca(mem_type, mem_count, "argc");
  builder->CreateStore(int32_ac, mem);
  codeGen.registerValue("argc", mem);

  mem_type = ptr_av->getType();
  mem_count = builder->getInt32(1);
  mem = builder->CreateAlloca(mem_type, mem_count, "argv");
  builder->CreateStore(ptr_av, mem);
  codeGen.registerValue("argv", mem);

  // create exit block. we should jump here when we run out of nodes
  BasicBlock *exit_block = BasicBlock::Create(*context, "exit_block", main_fn);

  builder->SetInsertPoint(main_block);

  auto value = n->compileBlock(codeGen, exit_block);

  builder->SetInsertPoint(exit_block);
  builder->CreateRet(get_exit_value(value));

  delete builder;

  if (log.isLogLevel(DEBUG) ||
      (getenv("SN_DUMP_PROGRAM") != nullptr &&
       strcmp(getenv("SN_DUMP_PROGRAM"), "true") == 0)) {
    TheModule->dump();
    printf("; end\n\n");
  }

  write(TheModule);

  module = TheModule;
  return TheModule;
}

void Compiler::write(const Module *m) {
  const char *filename = "program.bc";

  log.info("Writing program to '%s'. Compile with clang program.bc -o program",
           filename);

  std::error_code errorInfo;
  raw_fd_ostream myfile(filename, errorInfo, llvm::sys::fs::F_None);

  WriteBitcodeToFile(m, myfile);
}
}
