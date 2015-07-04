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

  BasicBlock *def_block = builder->GetInsertBlock();
  // s_assert_notnull(def_block);
  codeGen.setDefInsertPoint(def_block);

  llvm::Type *int8_ptr_type = llvm::Type::getInt8PtrTy(*context);
  llvm::Type *int32_type = IntegerType::get(*context, 32);

  // puts
  std::vector<llvm::Type *> puts_args(1, int8_ptr_type);
  FunctionType *puts_ft =
      FunctionType::get(llvm::Type::getInt32Ty(*context), puts_args, false);
  /*
  Function* puts_fn = Function::Create(puts_ft, Function::ExternalLinkage,
  "puts", TheModule);
  codeGen.registerFunction(puts_fn);
  */

  // atoi
  Function *atoi_fn =
      Function::Create(puts_ft, Function::ExternalLinkage, "atoi", TheModule);
  codeGen.registerFunction(atoi_fn);

  // getenv
  std::vector<llvm::Type *> getenv_args(1, int8_ptr_type);
  FunctionType *getenv_ft =
      FunctionType::get(int8_ptr_type, getenv_args, false);
  Function *getenv_fn = Function::Create(getenv_ft, Function::ExternalLinkage,
                                         "getenv", TheModule);
  codeGen.registerFunction(getenv_fn);

  // printf
  std::vector<llvm::Type *> printf_ft_args;
  printf_ft_args.push_back(int8_ptr_type);
  FunctionType *printf_ft = FunctionType::get(int32_type, printf_ft_args, true);
  Function *printf_fn = Function::Create(printf_ft, Function::ExternalLinkage,
                                         "printf", TheModule);
  codeGen.registerFunction(printf_fn);

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

  Node *current = n;
  Value *value = NULL;

  while (current != NULL) {
    value = current->compile(codeGen);
    current = current->getNext();
  }

  builder->CreateRet(get_exit_value(value));
  delete builder;

  if (log.isLogLevel(DEBUG)) {
    TheModule->dump();
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
