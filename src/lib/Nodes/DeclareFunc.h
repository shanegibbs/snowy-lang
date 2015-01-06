#ifndef OPAL_NODES_DECLARE_FUNC_H
#define OPAL_NODES_DECLARE_FUNC_H

#include "Statement.h"
#include "Type.h"
#include "ArgsDecl.h"
#include "Ident.h"
#include "Expression.h"

namespace Snowy
{

class DeclareFunc : public Statement
{
public:
    DeclareFunc(Type*, Ident*, ArgsDecl*, Node*);

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(std::ostringstream&) const;

private:
    static const Log log;
    Type *type;
    Ident *ident;
    ArgsDecl *args;
    Node *block;
};

}
#endif

