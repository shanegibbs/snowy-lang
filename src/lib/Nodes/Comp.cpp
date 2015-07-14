#include <stdio.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>

#include <SnowyAssert.h>
#include "Type.h"
#include "Comp.h"

using namespace llvm;

namespace Snowy {

const Log Comp::log = Log("Comp");

static const CompType parseOp(const shared_ptr<const string> o) {
  return COMP_EQ;
}

Comp::Comp(Expression *l, const shared_ptr<const string> o, Expression *r)
    : op(parseOp(o)), lhs(l), rhs(r) {
  s_assert_notnull(lhs);
  s_assert_notnull(rhs);
}

Comp::~Comp() {
  delete lhs;
  delete rhs;
}

const TypePtr Comp::getType() const {
  return TypePtr(new Type(shared_ptr<string>(new string("bool"))));
}

Value *Comp::compile(CodeGen &) const {
  log.fatal("Need to implement Comp.compile()");
  return nullptr;
}
}