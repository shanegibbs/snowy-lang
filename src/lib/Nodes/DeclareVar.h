#ifndef OPAL_NODES_DECLARE_VAR_H
#define OPAL_NODES_DECLARE_VAR_H

#include "Statement.h"

namespace Snowy
{

class Ident;
class Type;

class DeclareVar final : public Statement
{

public:
    DeclareVar(Ident*, const Expression*);
    virtual ~DeclareVar();

    DeclareVar* clone() const override final;

    const string& getName() const;

    const Ident& getIdent() const;

    const Expression& getExpression() const;

    NodeType getNodeType() const override final { return DECLARE_VAR; }

    const TypePtr getType() const override final;

    llvm::Value* compile(CodeGen&) const  override final;

    void to_sstream(std::ostringstream&) const override final;

private:
    static const Log log;
    Ident* ident;
    const Expression* expr;
};

}
#endif
