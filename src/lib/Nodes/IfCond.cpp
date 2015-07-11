#include <string.h>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>
#include <Type.h>

#include "IfCond.h"

using namespace llvm;

namespace Snowy {

const Log IfCond::log = Log("IfCond");

IfCond::IfCond(const Expression *c, const Node *b) : cond(c), block(b) {
  log.debug("Creating IfCond node");
  if (b != nullptr)
    s_assert(b == b->getFirst());  // a block must be the first node
};

void IfCond::to_sstream(std::ostringstream &s) const {
  s_assert(cond);
  s << "IfCond=[cond=[";
  cond->to_sstream(s);
  s << "] then=[" << endl;
  s << block->to_program_string();
  s << "]]";
}

Value *IfCond::compile(CodeGen &gen) const {
  log.debug("Compiling if cond");
  LLVMContext *c = &gen.getBuilder()->getContext();
  IRBuilder<> &b = *gen.getBuilder();

  TypePtr t = cond->getType();
  if (strcmp(t->getId().c_str(), "bool") != 0) {
    log.fatal("If condition must result in bool. Was: %s", t->getId().c_str());
  }

  Value *truth = cond->compile(gen);
  Value *const_yes = ConstantInt::get(*c, APInt(1, 1, false));

  Function *parent = gen.getCurrentFunc();

  BasicBlock *label_if_then = BasicBlock::Create(*c, "if.then", parent);
  BasicBlock *label_if_end = BasicBlock::Create(*c, "if.end", parent);

  auto icmp = new ICmpInst(*b.GetInsertBlock(), ICmpInst::ICMP_EQ, truth,
                           const_yes, "cmp");

  BranchInst::Create(label_if_then, label_if_end, icmp, b.GetInsertBlock());

  gen.getBuilder()->SetInsertPoint(label_if_then);
  block->compileBlock(gen, label_if_end);

  gen.getBuilder()->SetInsertPoint(label_if_end);

  return icmp;
}
}
