#ifndef OPAL_NODES_DECLARE_FUNC_H
#define OPAL_NODES_DECLARE_FUNC_H

#include "Statement.h"
#include "Type.h"
#include "Ident.h"
#include "Expression.h"

namespace Snowy
{

class DeclareFunc : public Statement
{
public:
    DeclareFunc(Type*, Ident*, Expression*) {}

    llvm::Value* compile(CodeGen*) const { return NULL; }

    void to_sstream(std::ostringstream*) const {}

private:
};

}
#endif

