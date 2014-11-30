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

namespace Snowy
{

const Log Compiler::log = Log("Compiler");

Module* Compiler::compile(Node* n)
{
    log.info("Compiling");


    LLVMContext &Context = getGlobalContext();

    IRBuilder<>* builder = new IRBuilder<>(Context);

    Module *TheModule = new Module("my jit", Context);

    CodeGen codeGen = CodeGen(builder, TheModule);

    // puts
    std::vector<Type*> puts_args(1, Type::getInt8PtrTy(Context));
    FunctionType *puts_ft = FunctionType::get(Type::getInt32Ty(Context), puts_args, false);
    Function* puts_fn = Function::Create(puts_ft, Function::ExternalLinkage, "puts", TheModule);
    codeGen.registerFunction(puts_fn);

    // main
    std::vector<Type*> main_args(2, Type::getInt8PtrTy(Context));
    FunctionType *main_ft = FunctionType::get(Type::getInt32Ty(Context), main_args, false);
    Function *main_fn = Function::Create(main_ft, Function::ExternalLinkage, "main", TheModule);

    BasicBlock *main_block = BasicBlock::Create(Context, "", main_fn);
    builder->SetInsertPoint(main_block);

    Node* current = n;
    while (current != NULL) {
        current->compile(&codeGen);
        current = current->getNext();
    }

    builder->SetInsertPoint(main_block);
    builder->CreateRet(ConstantInt::get(Context, APInt(32, 3, false)));

    if (log.isLogLevel(DEBUG)) {
        TheModule->dump();
    }

    write(TheModule);

    return TheModule;
}

void Compiler::write(const Module *m)
{
    const char* filename = "program.bc";

    log.info("Writing program to '%s'. Compile with clang program.bc -o program", filename);

    string errorInfo;
    raw_fd_ostream myfile(filename, errorInfo, llvm::sys::fs::OpenFlags::F_None);

    WriteBitcodeToFile(m, myfile);
}

}
