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
    DeclareFunc(const Type*, const Ident*, const ArgsDecl*, const Node*);
    ~DeclareFunc();

    DeclareFunc* clone() const
    {
        return new DeclareFunc(*this);
    }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(std::ostringstream&) const;

private:
    static const Log log;
    const Type* type;
    const Ident* ident;
    const ArgsDecl* args;
    const Node* block;
};

}
#endif

