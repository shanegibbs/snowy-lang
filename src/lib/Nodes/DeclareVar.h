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
    DeclareVar(const Ident*, const Expression*);
    virtual ~DeclareVar();

    DeclareVar* clone() const
    {
        return new DeclareVar(*this);
    }

    const string& getName() const {
        return *ident->getName();
    }

    const Expression& getExpression() const {
        return *expr;
    }

    NodeType getNodeType() const override { return DECLARE_VAR; }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(std::ostringstream&) const;

private:
    static const Log log;
    const Ident* ident;
    const Expression* expr;
};

}
#endif
