#include <stdio.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>

#include "Tuple.h"

using namespace llvm;

namespace Snowy
{

Tuple::Tuple(Expression *l, Operator *o, Expression *r)
{
    lhs = l;
    rhs = r;
    op = o;
}

Value* Tuple::compile(CodeGen* gen) const
{
    Value* lhs_val = lhs->compile(gen);
    Value* rhs_val = rhs->compile(gen);

    IRBuilder<>* b = gen->getBuilder();

    return b->CreateAdd(lhs_val, rhs_val, "tuple");
}

void Snowy::Tuple::to_sstream(std::ostringstream* s) const
{
    *s << "Tuple=[lhs=[";
    lhs->to_sstream(s);
    *s << "] op=[";
    op->to_sstream(s);
    *s << "] rhs=[";
    rhs->to_sstream(s);
    *s << "]]";
}

}
