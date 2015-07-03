#ifndef OPAL_NODES_IF_H
#define OPAL_NODES_IF_H

#include "Statement.h"

namespace Snowy {

class Ident;
class Type;

class IfLogic final : public Statement {
 public:
  IfLogic(const Expression *e, const Node *n) {
    expr = e;
    block = n;
  };
  virtual ~IfLogic() {
    delete expr;
    delete block;
  };

  IfLogic *clone() const override final { return nullptr; };

  NodeType getNodeType() const override final { return DECLARE_VAR; }

  const TypePtr getType() const override final { return nullptr; };

  llvm::Value *compile(CodeGen &) const override final { return nullptr; };

  void to_sstream(std::ostringstream &) const override final{};

 private:
  static const Log log;
  const Expression *expr;
  const Node *block;
};
}
#endif
