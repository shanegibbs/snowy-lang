#ifndef OPAL_NODES_COMP_H
#define OPAL_NODES_COMP_H

#include "Expression.h"

using namespace std;

namespace Snowy {

class Log;

enum CompType { COMP_EQ, COMP_NEQ };

class Comp final : public Expression {
 public:
  Comp(Expression *, const shared_ptr<const string>, Expression *);
  ~Comp();

  Comp *clone() const override { return new Comp(*this); };

  const TypePtr getType() const override final;

  NodeType getNodeType() const override final { return COMP; }

  llvm::Value *compile(CodeGen &) const override final;

  void to_sstream(ostringstream &) const override final {}

 private:
  static const Log log;
  const CompType op;
  const Expression *lhs;
  const Expression *rhs;
};
}
#endif
