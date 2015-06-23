#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "Type.h"
#include "Ident.h"
#include "DeclareVar.h"

using namespace llvm;

namespace Snowy
{

const Log DeclareVar::log = Log("DeclareVar");

DeclareVar::DeclareVar(Ident *i, const Expression* e) : ident(i), expr(e)
{
    s_assert_notnull(ident);
    s_assert_notnull(expr);

    log.debug("Creating DeclareVar '%s'", ident->getName()->c_str());

    if (ident->getType() == nullptr) {
        ident->setType(expr->getType());
    } else {
        if (ident->getType() != expr->getType()) {
            log.ui("Type mismatch, can not assign %s to %s",
                    expr->getType()->getId().c_str(),
                    ident->getType()->getId().c_str());
        }
    }
}

DeclareVar::~DeclareVar()
{
    log.debug("Deleting DeclareVar '%s'", ident->getName()->c_str());
    delete ident;
    delete expr;
}

DeclareVar* DeclareVar::clone() const
{
    return new DeclareVar(*this);
}

const Type* DeclareVar::getType() const
{
    return expr->getType();
}

const string& DeclareVar::getName() const {
    return *ident->getName();
}

const Ident& DeclareVar::getIdent() const {
    return *ident;
}

const Expression& DeclareVar::getExpression() const {
    return *expr;
}

void DeclareVar::to_sstream(std::ostringstream& s) const
{
    s_assert_notnull(ident);
    s_assert_notnull(expr);

    s << "DeclareVar=[ident=[";
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
    AllocaInst* mem = b->CreateAlloca(mem_type, mem_count, *ident->getName());

    StoreInst* stored = b->CreateStore(val, mem);
    gen.registerValue(*ident->getName(), mem);

    return stored;
}

}
