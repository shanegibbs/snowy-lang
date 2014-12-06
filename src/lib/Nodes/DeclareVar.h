#ifndef OPAL_NODES_DECLARE_VAR_H
#define OPAL_NODES_DECLARE_VAR_H

#include "Statement.h"
#include "Type.h"
#include "Ident.h"
#include "Expression.h"

namespace Snowy
{

class DeclareVar : public Statement
{
public:
    DeclareVar(Type*, Ident*, Expression*);

    llvm::Value* compile(CodeGen*) const;

    void to_sstream(std::ostringstream*) const;

private:
    Type *type;
    Ident *ident;
    Expression *expr;
};

}
#endif
