#ifndef OPAL_NODES_FUNC_DEF_H
#define OPAL_NODES_FUNC_DEF_H

#include "Statement.h"

namespace Snowy
{

class Ident;
class ArgsDecl;
class Type;
class Log;

class FuncDef final : public Statement
{
public:
    FuncDef(const Ident*, const ArgsDecl*, const Node*);
    FuncDef();
    ~FuncDef();
    
    FuncDef* clone() const override final;

    const string& getName() const;

    NodeType getNodeType() const override final { return DECLARE_FUNC; }

    const Type* getType() const override final;

    llvm::Value* compile(CodeGen&) const override final;

    void to_sstream(std::ostringstream&) const override final;

private:
    static const Log log;
    const Ident* ident;
    const ArgsDecl* args;
    const Node* block;
};

}
#endif
