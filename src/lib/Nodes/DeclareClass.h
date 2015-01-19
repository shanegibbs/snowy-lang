#ifndef OPAL_NODES_DECLARE_CLASS_H
#define OPAL_NODES_DECLARE_CLASS_H

#include <vector>

#include "SnowyAssert.h"
#include "Ident.h"
#include "Expression.h"

namespace Snowy
{

class DeclareVar;
class DeclareFunc;

class DeclareClass : public Expression
{
public:
    DeclareClass();
    DeclareClass(Type*);
    ~DeclareClass();

    DeclareClass* clone() const
    {
        return new DeclareClass(*this);
    }

    NodeType getNodeType() const override
    {
        return DECLARE_CLASS;
    }

    void setType(Type* t)
    {
        type = t;
    }

    void addVarDecl(DeclareVar* v)
    {
        vars.push_back(v);
    }

    void addFuncDecl(DeclareFunc* v)
    {
        funcs.push_back(v);
    }

    vector<DeclareVar*>& getVars()
    {
        return vars;
    }

    vector<DeclareFunc*>& getFuncs()
    {
        return funcs;
    }

    Type& getType() const
    {
        s_assert_notnull(type);
        return *type;
    }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(std::ostringstream&) const;

private:
    static const Log log;
    Type* type;
    vector<DeclareVar*> vars;
    vector<DeclareFunc*> funcs;
};

}
#endif


