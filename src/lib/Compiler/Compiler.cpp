#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Support/TargetSelect.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>

#include "Compiler.h"

using namespace llvm;

namespace Snowy
{

void Compiler::compile(Node *n)
{
    puts("Compiling");

    InitializeNativeTarget();

    LLVMContext &Context = getGlobalContext();

    IRBuilder<> builder(Context);

    Module *TheModule = new Module("my jit", Context);

    // puts
    std::vector<Type*> puts_args(1, Type::getInt8PtrTy(Context));
    FunctionType *puts_ft = FunctionType::get(Type::getInt32Ty(Context), puts_args, false);
    Function::Create(puts_ft, Function::ExternalLinkage, "puts", TheModule);

    // main
    std::vector<Type*> main_args(2, Type::getInt8PtrTy(Context));
    FunctionType *main_ft = FunctionType::get(Type::getInt32Ty(Context), main_args, false);
    Function *main_fn = Function::Create(main_ft, Function::ExternalLinkage, "main", TheModule);

    BasicBlock *main_block = BasicBlock::Create(Context, "", main_fn);
    builder.SetInsertPoint(main_block);

    n->compile(&builder);

    builder.SetInsertPoint(main_block);
    builder.CreateRet(ConstantInt::get(Context, APInt(32, 3, false)));

    TheModule->dump();

    puts("Executing program:\n");

    std::string ErrStr;
    ExecutionEngine *TheExecutionEngine = EngineBuilder(TheModule).setErrorStr(&ErrStr).create();
    if (!TheExecutionEngine) {
        fprintf(stderr, "Could not create ExecutionEngine: %s\n", ErrStr.c_str());
        exit(1);
    }

    TheModule->setDataLayout(TheExecutionEngine->getDataLayout());

    void *main_fn_ptr = TheExecutionEngine->getPointerToFunction(main_fn);
    int (*program_main)(int, int) = (int (*)(int, int))main_fn_ptr;
    int ret = program_main(2, 4);
    fprintf(stderr, "main returned %i\n", ret);

}

}
