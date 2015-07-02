#ifndef OPAL_NODES_IDENT_H
#define OPAL_NODES_IDENT_H

#include <memory>
#include <string>

#include "Expression.h"

using namespace std;

namespace Snowy {

  class Log;

  class Ident final : public Expression {
   public:
    Ident(const shared_ptr<const string>);
    Ident(const shared_ptr<const string>, const TypePtr);
    ~Ident();

    Ident *clone() const override;

    const string *getName() const;

    const TypePtr getType() const override final;

    void setType(const TypePtr);

    NodeType getNodeType() const override final { return IDENT; }

    llvm::Value *compile(CodeGen &) const override final;

    void to_sstream(ostringstream &) const override final;

   private:
    static const Log log;
    void init();
    const shared_ptr<const string> name;
    TypePtr type;
  };

}
#endif
