#ifndef OPAL_NODES_EXPRESSION_H
#define OPAL_NODES_EXPRESSION_H

#include "Node.h"

namespace Snowy
{

class Expression : public Node
{
public:
    Expression() {}
    llvm::Value* compile(CodeGen*) const
    {
        return NULL;
    }
    void to_sstream(std::ostringstream*) const {}
};

}
#endif
