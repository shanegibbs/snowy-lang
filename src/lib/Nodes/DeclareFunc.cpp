#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "DeclareFunc.h"

using namespace llvm;

namespace Snowy
{

const Log DeclareFunc::log = Log("DeclareFunc");

DeclareFunc::DeclareFunc(Type* t, Ident *i, ArgsDecl* a, Node* b)
{
    log.debug("Creating DeclarerFunc node %d", getId());
    type = t;
    ident = i;
    args = a;
    block = b;
}

void DeclareFunc::to_sstream(std::ostringstream* s) const
{
    s_assert_notnull(type);
    s_assert_notnull(ident);
    s_assert_notnull(args);

    *s << "DeclareFunc=[type=[";
    type->to_sstream(s);
    *s << "] ident=[";
    ident->to_sstream(s);
    *s << "] args=[";
    args->to_sstream(s);
    *s << "] block=[";
    if (block == NULL) {
        *s << "NULL";
    } else {
        Node* current = block;
        while (current != NULL) {
            current->to_sstream(s);
            *s << endl;
            current = current->getNext();
        }
    }
    *s << "]]";
}

Value* DeclareFunc::compile(CodeGen* gen) const
{
    s_assert_notnull(type);
    s_assert_notnull(ident);
    s_assert_notnull(args);

    LLVMContext* context = &gen->getBuilder()->getContext();

    // TODO map types
    std::vector<llvm::Type*> fn_args(args->getCount());
    for (unsigned int i = 0; i < args->getCount(); i++) {
    }

    FunctionType *ft = FunctionType::get(llvm::Type::getInt32Ty(*context), fn_args, false);

    Function* fn = Function::Create(ft, Function::ExternalLinkage, ident->getName(), gen->getModule());
    gen->registerFunction(fn);

    BasicBlock *bb = BasicBlock::Create(getGlobalContext(), "entry", fn);
    BasicBlock* last_block = gen->getBuilder()->GetInsertBlock();
    gen->getBuilder()->SetInsertPoint(bb);
    gen->getBuilder()->CreateRet(block->compile(gen));

    gen->getBuilder()->SetInsertPoint(last_block);

    return fn;
}

}
