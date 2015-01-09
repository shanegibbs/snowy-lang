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
    DeclareVar(const Type*, const Ident*, const Expression*);

    DeclareVar* clone() const
    {
        return new DeclareVar(*this);
    }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(std::ostringstream&) const;

private:
    static const Log log;
    const Type* type;
    const Ident* ident;
    const Expression* expr;
};

}
#endif
