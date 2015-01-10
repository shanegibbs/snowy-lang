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

Compiler::Compiler()
{
    context = new LLVMContext();
}

Compiler::~Compiler()
{
    delete context;
}

Value* Compiler::get_exit_value(Value* last_val)
{
    Value* zero = ConstantInt::get(*context, APInt(32, 0, false));

    if (last_val == NULL) {
        log.debug("Last value was NULL. Setting exit code to 0");
        return zero;
    }
    Type *retType = last_val->getType();
    if (retType->isIntegerTy(32)) {
        log.debug("Last value was i32. Setting exit code to last_val");
        return last_val;
    } else {
        log.debug("Last value was not i32. Setting exit code to 0");
        return ConstantInt::get(*context, APInt(32, 0, false));
    }
}

Module* Compiler::compile(Node* n)
{
    log.info("Compiling");

    IRBuilder<>* builder = new IRBuilder<>(*context);

    Module *TheModule = new Module("program.snowy", *context);

    CodeGen codeGen = CodeGen(builder, TheModule);

    // puts
    Type* ptr_type = Type::getInt8PtrTy(*context);
    std::vector<Type*> puts_args(1, ptr_type);
    FunctionType *puts_ft = FunctionType::get(Type::getInt32Ty(*context), puts_args, false);
    Function* puts_fn = Function::Create(puts_ft, Function::ExternalLinkage, "puts", TheModule);
    codeGen.registerFunction(puts_fn);

    // main
    std::vector<Type*> main_args(2, Type::getInt8PtrTy(*context));
    FunctionType *main_ft = FunctionType::get(Type::getInt32Ty(*context), main_args, false);
    Function *main_fn = Function::Create(main_ft, Function::ExternalLinkage, "main", TheModule);

    BasicBlock *main_block = BasicBlock::Create(*context, "", main_fn);
    builder->SetInsertPoint(main_block);

    Node* current = n;
    Value* value = NULL;
    while (current != NULL) {
        value = current->compile(codeGen);
        current = current->getNext();
    }

    builder->SetInsertPoint(main_block);
    builder->CreateRet(get_exit_value(value));
    delete builder;

    if (log.isLogLevel(DEBUG)) {
        TheModule->dump();
    }

    write(TheModule);

    module = TheModule;
    return TheModule;
}

void Compiler::write(const Module *m)
{
    const char* filename = "program.bc";

    log.info("Writing program to '%s'. Compile with clang program.bc -o program", filename);

    string errorInfo;
    raw_fd_ostream myfile(filename, errorInfo, llvm::sys::fs::F_None);

    WriteBitcodeToFile(m, myfile);
}

}
