#ifndef OPAL_NODES_STATEMENT_H
#define OPAL_NODES_STATEMENT_H

#include "Node.h"

namespace Snowy
{

class Statement : public Node
{
public:
    Statement() {}

    virtual llvm::Value* compile(CodeGen&) const = 0;
    virtual void to_sstream(std::ostringstream&) const = 0;

};

}
#endif
