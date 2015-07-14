#ifndef OPAL_NODES_BOOL_LITERAL_H
#define OPAL_NODES_BOOL_LITERAL_H

#include "Expression.h"
#include "Type.h"

using namespace std;

namespace Snowy {

class BoolLiteral : public Expression {
 public:
  BoolLiteral(const shared_ptr<const string>);

  BoolLiteral *clone() const override { return new BoolLiteral(*this); }

  const TypePtr getType() const override final {
    return TypePtr(new Type(shared_ptr<string>(new string("bool"))));
  }

  NodeType getNodeType() const override final { return BOOL_LITERAL; }

  llvm::Value *compile(CodeGen &) const override;

  void to_sstream(ostringstream &) const override;

 private:
  static const Log log;
  const bool val;
};
}
#endif
