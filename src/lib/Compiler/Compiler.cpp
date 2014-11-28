#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Support/TargetSelect.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>

#include <Log.h>
#include <Call.h>

#include "CodeGen.h"
#include "Compiler.h"

using namespace llvm;

namespace Snowy
{

const Log Compiler::log = Log("Compiler");

int Compiler::compile(Node* n)
{
    log.info("Compiling");

    InitializeNativeTarget();

    LLVMContext &Context = getGlobalContext();

    IRBuilder<> builder(Context);

    Module *TheModule = new Module("my jit", Context);

    CodeGen codeGen = CodeGen(&builder, TheModule);

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
    builder.SetInsertPoint(main_block);

    Node* current = n;
    while (current != NULL) {
        current->compile(&codeGen);
        current = current->getNext();
    }

    builder.SetInsertPoint(main_block);
    builder.CreateRet(ConstantInt::get(Context, APInt(32, 3, false)));

    if (log.isLogLevel(DEBUG)) {
        TheModule->dump();
    }

    log.info("Executing program");

    std::string ErrStr;
    ExecutionEngine *TheExecutionEngine = EngineBuilder(TheModule).setErrorStr(&ErrStr).create();
    if (!TheExecutionEngine) {
        log.fatal("Could not create ExecutionEngine: %s", ErrStr.c_str());
        exit(1);
    }

    TheModule->setDataLayout(TheExecutionEngine->getDataLayout());

    void *main_fn_ptr = TheExecutionEngine->getPointerToFunction(main_fn);
    int (*program_main)(int, int) = (int (*)(int, int))main_fn_ptr;
    int ret = program_main(2, 4);
    log.info("main returned %i", ret);

    return ret;
}

}
