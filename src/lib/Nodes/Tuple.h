#ifndef OPAL_NODES_TUPLE_H
#define OPAL_NODES_TUPLE_H

#include "Expression.h"

namespace Snowy {

class Operator;

class Tuple final : public Expression {
 public:
  Tuple(Expression *, Operator *, Expression *);
  ~Tuple();

  Tuple *clone() const override final { return new Tuple(*this); }

  NodeType getNodeType() const override final { return TUPLE; }

  const TypePtr getType() const override final;

  llvm::Value *compile(CodeGen &) const override final;

  void to_sstream(std::ostringstream &) const override final;

 private:
  static const Log log;
  const Expression *lhs;
  const Expression *rhs;
  const Operator *op;
};
}
#endif
