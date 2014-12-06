#include <glib.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>

#include "DeclareVar.h"

using namespace llvm;

namespace Snowy
{

DeclareVar::DeclareVar(Type* t, Ident *i, Expression* e)
{
    g_debug("Creating DeclareVar node %d", getId());
    type = t;
    ident = i;
    expr = e;
}

void DeclareVar::to_sstream(std::ostringstream* s) const
{
    g_assert_nonnull(ident);
    g_assert_nonnull(expr);

    *s << "DeclareVar=[type=[";
    type->to_sstream(s);
    *s << "] ident=[";
    ident->to_sstream(s);
    *s << "] expr=[";
    expr->to_sstream(s);
    *s << "]]";
}

Value* DeclareVar::compile(CodeGen* gen) const
{
    Value *val = expr->compile(gen);
    g_assert_nonnull(val);

    // IntegerType* mem_type = llvm::Type::getInt32Ty(*c);
    llvm::Type* mem_type = val->getType();
    ConstantInt* mem_count = gen->getBuilder()->getInt32(1);
    AllocaInst* mem = gen->getBuilder()->CreateAlloca(mem_type, mem_count, ident->getName());

    StoreInst* stored = gen->getBuilder()->CreateStore(val, mem);
    return stored;
}

}
