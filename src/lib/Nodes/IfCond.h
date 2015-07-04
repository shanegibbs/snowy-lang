#ifndef OPAL_NODES_IF_H
#define OPAL_NODES_IF_H

#include "Statement.h"

namespace Snowy {

class Ident;
class Type;

class IfCond final : public Statement {
 public:
  IfCond(const Expression *c, const Node *b = nullptr) {
    cond = c;
    block = b;
  };
  virtual ~IfCond() {
    delete cond;
    if (block != nullptr) delete block;
  };

  IfCond *clone() const override final { return new IfCond(*this); };

  NodeType getNodeType() const override final { return IF_CONF; }

  const TypePtr getType() const override final {
    log.fatal("IfCond.getType() not implemented");
    return nullptr;
  };

  llvm::Value *compile(CodeGen &) const override final;

  void to_sstream(std::ostringstream &) const override;

 private:
  static const Log log;
  const Expression *cond;
  const Node *block;
};
}
#endif
