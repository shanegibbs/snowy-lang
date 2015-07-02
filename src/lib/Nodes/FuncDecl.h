#ifndef OPAL_NODES_FUNC_DECL_H
#define OPAL_NODES_FUNC_DECL_H

#include "Callable.h"

namespace Snowy {

  class Ident;
  class ArgsDecl;
  class Log;

  class FuncDecl : public Callable {

   public:

    FuncDecl(const Ident *, const ArgsDecl *);

    FuncDecl *clone() const override final;
    llvm::Value *compile(CodeGen &) const override final;
    void to_sstream(std::ostringstream &) const override final;

    NodeType getNodeType() const override final { return FUNC_DECL; }

   private:

    static const Log log;

  };

}
#endif
