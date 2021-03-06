#ifndef SNOWY_NODES_CALL_H
#define SNOWY_NODES_CALL_H

#include "Expression.h"

namespace Snowy {

class Callable;
class Args;
class Log;

class Call final : public Expression {
 public:
  Call(const Callable *, const Args *);
  ~Call();

  Call *clone() const override final;

  NodeType getNodeType() const override final { return CALL; }

  const TypePtr getType() const override final;

  llvm::Value *compile(CodeGen &) const override final;

  void to_sstream(std::ostringstream &) const override final;

 private:
  static const Log log;
  const Callable *func;
  const Args *args;
};
}
#endif
