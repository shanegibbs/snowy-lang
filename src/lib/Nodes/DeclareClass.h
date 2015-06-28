#ifndef OPAL_NODES_DECLARE_CLASS_H
#define OPAL_NODES_DECLARE_CLASS_H

#include <vector>

#include "SnowyAssert.h"
#include "Expression.h"

namespace Snowy
{

class DeclareVar;
class FuncDef;

class DeclareClass final : public Expression
{
public:
    DeclareClass();
    DeclareClass(Type*);
    ~DeclareClass();

    DeclareClass* clone() const override final;

    NodeType getNodeType() const override final;

    void setType(const Type* t);

    void addVarDecl(DeclareVar* v);

    void addFuncDecl(FuncDef* v);

    vector<DeclareVar*>& getVars();

    vector<FuncDef*>& getFuncs();

    const Type* getType() const override final;

    const Type& getClassType() const;

    llvm::Value* compile(CodeGen&) const override final;

    void to_sstream(std::ostringstream&) const override final;

private:
    static const Log log;
    const Type* type;
    vector<DeclareVar*> vars;
    vector<FuncDef*> funcs;
};

}
#endif
