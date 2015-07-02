#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Support/TargetSelect.h>

#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>

/*
extern "C" {
#include "nodes.h"
}

void print_node(Node *node)
{
  while (node != NULL)
  {
    printf("%s\n", get_node_desc(node));
    node = node->node_next;
  }
}

int current_prog()
{
  // opal_parse_string("1+2\n");
  opal_stdin_parse();

  if (root == NULL)
  {
    printf("root is NULL\n");
    return 3;
  }

  printf("\nPrinting node graph:\n");
  print_node(root);

  return 0;
}
*/

int test_program() {
  llvm::InitializeNativeTarget();

  llvm::LLVMContext &Context = llvm::getGlobalContext();

  llvm::IRBuilder<> Builder(Context);

  llvm::Module *TheModule = new llvm::Module("my jit", Context);


  // str
  const char *str_value = "hello world";

  llvm::ArrayType *str_arr_ty = llvm::ArrayType::get(llvm::Type::getInt8Ty(Context), strlen(str_value) + 1);
  llvm::StringRef str_ref(str_value, strlen(str_value));
  llvm::Constant *str_init = llvm::ConstantDataArray::getString(Context, str_ref, true);

  llvm::GlobalVariable *my_str = new llvm::GlobalVariable(*TheModule, str_arr_ty, true, llvm::GlobalValue::ExternalLinkage, str_init, "my_str");

  // puts
  std::vector<llvm::Type *> puts_args(1, llvm::Type::getInt8PtrTy(Context));
  llvm::FunctionType *puts_ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), puts_args, false);
  llvm::Function::Create(puts_ft, llvm::Function::ExternalLinkage, "puts", TheModule);

  // main
  std::vector<llvm::Type *> main_args(2, llvm::Type::getInt8PtrTy(Context));
  llvm::FunctionType *main_ft = llvm::FunctionType::get(llvm::Type::getInt32Ty(Context), main_args, false);
  llvm::Function *main_fn = llvm::Function::Create(main_ft, llvm::Function::ExternalLinkage, "main", TheModule);

  llvm::BasicBlock *main_block = llvm::BasicBlock::Create(Context, "", main_fn);
  Builder.SetInsertPoint(main_block);

  llvm::Constant *foo[2] = { llvm::ConstantInt::get(Context, llvm::APInt(8, 0, false)), llvm::ConstantInt::get(Context, llvm::APInt(8, 0, false)) };

  llvm::ArrayRef<llvm::Constant *> idx(foo, 2);
  llvm::Constant *my_str_ptr = llvm::ConstantExpr::getGetElementPtr(my_str, idx);

  std::vector<llvm::Value *> ArgsV;
  ArgsV.push_back(my_str_ptr);
  std::string puts_name("puts");
  llvm::Function *puts_fn = TheModule->getFunction(puts_name);
  Builder.CreateCall(puts_fn, ArgsV, "puts_result");
  Builder.CreateRet(llvm::ConstantInt::get(Context, llvm::APInt(32, 3, false)));

  // llvm::Function::arg_iterator args_i = F->arg_begin();
  // llvm::Value* x = args_i++;
  // x->setName("a");
  // llvm::Value* y = args_i++;
  // y->setName("b");

  /*
  llvm::Value *L = llvm::ConstantInt::get(Context, llvm::APInt(8, 2, false));
  llvm::Value *R = llvm::ConstantInt::get(Context, llvm::APInt(8, 3, false));

  llvm::Value *b = Builder.CreateAdd(L, R, "addtmp");

  Builder.CreateRet(b);

  llvm::Value *arg_a = llvm::ConstantInt::get(Context, llvm::APInt(8, 2, false));
  llvm::Value *arg_b = llvm::ConstantInt::get(Context, llvm::APInt(8, 3, false));

  std::vector<llvm::Value*> F_args;
  F_args.push_back(arg_a);
  F_args.push_back(arg_b);
  Builder.CreateCall(F, F_args, "calltmp");
  */

  TheModule->dump();
  puts("-------------------------------\n");

  puts("Executing program:\n");

  std::string ErrStr;
  llvm::ExecutionEngine *TheExecutionEngine = llvm::EngineBuilder(TheModule).setErrorStr(&ErrStr).create();

  if (!TheExecutionEngine) {
    fprintf(stderr, "Could not create ExecutionEngine: %s\n", ErrStr.c_str());
    exit(1);
  }

  TheModule->setDataLayout(TheExecutionEngine->getDataLayout()->getStringRepresentation());

  void *main_fn_ptr = TheExecutionEngine->getPointerToFunction(main_fn);
  int (*program_main)(int, int) = (int (*)(int, int))main_fn_ptr;
  int ret = program_main(2, 4);
  fprintf(stderr, "main returned %i\n", ret);

  return 0;
}


int main(int argc, char **argv) {
  return test_program();
}
