#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/MC/SubtargetFeature.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/FormattedStream.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ToolOutputFile.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>

#include <llvm/MC/MCELFObjectWriter.h>

#include <Log.h>
#include <Call.h>

#include "CodeGen.h"
#include "Compiler.h"

using namespace std;
using namespace llvm;

namespace Snowy {

const Log Compiler::log = Log("Compiler");

void Compiler::init() {
  InitializeAllTargets();
  InitializeAllTargetMCs();
  InitializeAllAsmPrinters();
  InitializeAllAsmParsers();
}

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

static string getFeaturesStr() {
  SubtargetFeatures Features;

  StringMap<bool> HostFeatures;
  if (sys::getHostCPUFeatures(HostFeatures)) {
    for (auto &F : HostFeatures) {
      if (F.second) Features.AddFeature(F.first());
    }
  }

  return Features.getString();
}

Module *Compiler::compile(Node *n) {
  log.info("Compiling");

  // Prints target archs that are supported:
  // TargetRegistry::printRegisteredTargetsForVersion();

  IRBuilder<> *builder = new IRBuilder<>(*context);

  Module *TheModule = new Module("org.default", *context);

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

  string error_str;
  llvm::raw_string_ostream oss(error_str);
  bool moduleFail = llvm::verifyModule(*TheModule, &oss);
  if (moduleFail) {
    log.fatal("Module is not good: %s", error_str.c_str());
    return nullptr;
  }
  log.info("Module verified");

  auto triple = sys::getDefaultTargetTriple();
  log.info("Using target architecture %s", triple.c_str());
  TheModule->setTargetTriple(triple);

  std::string err;
  const Target *target = TargetRegistry::lookupTarget(triple, err);
  if (!target) {
    log.fatal("Failed to get target: %s", err.c_str());
    return nullptr;
  }

  legacy::PassManager pm;

  string cpuStr = sys::getHostCPUName();
  string featuresStr = getFeaturesStr();

  TargetOptions options;

  std::unique_ptr<TargetMachine> machine(
      target->createTargetMachine(triple, cpuStr, featuresStr, options));

  // setup the output file
  error_code EC;
  sys::fs::OpenFlags OpenFlags = sys::fs::F_None;
  raw_fd_ostream rawStream("main.o", EC, OpenFlags);
  if (EC) {
    log.fatal(EC.message().c_str());
    return nullptr;
  }

  formatted_raw_ostream fStream(rawStream, false);

  if (machine->addPassesToEmitFile(pm, fStream,
                                   TargetMachine::CGFT_ObjectFile)) {
    log.fatal("Target does not support generation of this file type!\n");
    return nullptr;
  }

  pm.run(*TheModule);

  module = TheModule;
  return TheModule;
}
}
