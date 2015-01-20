#ifndef OPAL_NODES_EXPRESSION_H
#define OPAL_NODES_EXPRESSION_H

#include "Node.h"

namespace Snowy
{

class Type;

class Expression : public Node
{
public:
    Expression() {}
    virtual ~Expression() {};
    virtual Expression* clone() const = 0;

    virtual const Type* getType() const = 0;

    llvm::Value* compile(CodeGen&) const
    {
        return NULL;
    }
    void to_sstream(std::ostringstream&) const {}
};

}
#endif
