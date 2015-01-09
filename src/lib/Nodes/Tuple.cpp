#include <stdio.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>

#include <SnowyAssert.h>
#include "Tuple.h"

using namespace llvm;

namespace Snowy
{

Tuple::Tuple(Expression* l, Operator* o, Expression* r) : lhs(l), rhs(r), op(o)
{
    s_assert_notnull(lhs);
    s_assert_notnull(op);
    s_assert_notnull(rhs);
}

Tuple::~Tuple()
{
    delete lhs;
    delete rhs;
    delete op;
}

Value* Tuple::compile(CodeGen& gen) const
{
    Value* lhs_val = lhs->compile(gen);
    Value* rhs_val = rhs->compile(gen);

    IRBuilder<>* b = gen.getBuilder();

    switch(op->getOp()) {
    case OP_PLUS:
        return b->CreateAdd(lhs_val, rhs_val, "tuple");
    case OP_MINUS:
        return b->CreateSub(lhs_val, rhs_val, "tuple");
    case OP_MULTIPLY:
        return b->CreateMul(lhs_val, rhs_val, "tuple");
    case OP_DIVIDE:
        return b->CreateUDiv(lhs_val, rhs_val, "tuple");
    }

    s_assert_unreachable();
    return NULL;
}

void Snowy::Tuple::to_sstream(std::ostringstream& s) const
{
    s << "Tuple=[lhs=[";
    lhs->to_sstream(s);
    s << "] op=[";
    op->to_sstream(s);
    s << "] rhs=[";
    rhs->to_sstream(s);
    s << "]]";
}

}
