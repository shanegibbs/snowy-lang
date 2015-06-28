#ifndef OPAL_NODES_FUNC_DECL_H
#define OPAL_NODES_FUNC_DECL_H

#include "Statement.h"

namespace Snowy {

  class Ident;
  class ArgsDecl;
  class Type;
  class Log;

  class FuncDecl final : public Statement {
   public:
    FuncDecl(const Ident *, const ArgsDecl *);
    ~FuncDecl();

    FuncDecl *clone() const override final;

    const string &getName() const;

    NodeType getNodeType() const override final { return FUNC_DECL; }

    const TypePtr getType() const override final;

    llvm::Value *compile(CodeGen &) const override final;

    void to_sstream(std::ostringstream &) const override final;

   private:
    static const Log log;
    const Ident *ident;
    const ArgsDecl *args;
  };

}
#endif
