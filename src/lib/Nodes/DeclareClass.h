#ifndef OPAL_NODES_DECLARE_CLASS_H
#define OPAL_NODES_DECLARE_CLASS_H

#include <vector>

#include "SnowyAssert.h"
#include "Expression.h"

namespace Snowy
{

class DeclareVar;
class DeclareFunc;

class DeclareClass final : public Expression
{
public:
    DeclareClass();
    DeclareClass(Type*);
    ~DeclareClass();

    DeclareClass* clone() const override final;

    NodeType getNodeType() const override final;

    void setType(Type* t);

    void addVarDecl(DeclareVar* v);

    void addFuncDecl(DeclareFunc* v);

    vector<DeclareVar*>& getVars();

    vector<DeclareFunc*>& getFuncs();

    const Type* getType() const override final;

    Type& getClassType() const;

    llvm::Value* compile(CodeGen&) const override final;

    void to_sstream(std::ostringstream&) const override final;

private:
    static const Log log;
    Type* type;
    vector<DeclareVar*> vars;
    vector<DeclareFunc*> funcs;
};

}
#endif
