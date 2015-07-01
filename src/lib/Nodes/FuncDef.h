#ifndef OPAL_NODES_FUNC_DEF_H
#define OPAL_NODES_FUNC_DEF_H

#include "Callable.h"

namespace Snowy
{

class Ident;
class ArgsDecl;
class Type;
class Log;

class FuncDef final : public Callable
{
public:
    FuncDef(const Ident*, const ArgsDecl*, const Node*);
    ~FuncDef();
    
    FuncDef* clone() const override final;

    NodeType getNodeType() const override final { return FUNC_DEF; }

    llvm::Value* compile(CodeGen&) const override final;

    void to_sstream(std::ostringstream&) const override final;

private:
    static const Log log;
    const Node* block;
};

}
#endif
