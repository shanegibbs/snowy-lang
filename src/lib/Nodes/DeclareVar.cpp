#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "DeclareVar.h"

using namespace llvm;

namespace Snowy
{

const Log DeclareVar::log = Log("DeclareVar");

DeclareVar::DeclareVar(Type* t, Ident *i, Expression* e)
{
    log.debug("Creating DeclareVar node %d", getId());
    type = t;
    ident = i;
    expr = e;
}

void DeclareVar::to_sstream(std::ostringstream& s) const
{
    s_assert_notnull(ident);
    s_assert_notnull(expr);

    s << "DeclareVar=[type=[";
    type->to_sstream(s);
    s << "] ident=[";
    ident->to_sstream(s);
    s << "] expr=[";
    expr->to_sstream(s);
    s << "]]";
}

Value* DeclareVar::compile(CodeGen& gen) const
{
    Value *val = expr->compile(gen);
    s_assert_notnull(val);

    IRBuilder<>* b = gen.getBuilder();

    llvm::Type* mem_type = val->getType();
    ConstantInt* mem_count = b->getInt32(1);
    AllocaInst* mem = b->CreateAlloca(mem_type, mem_count, ident->getName());

    StoreInst* stored = b->CreateStore(val, mem);
    gen.registerValue(ident->getName(), mem);

    return stored;
}

}
