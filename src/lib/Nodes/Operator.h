#ifndef SNOWY_NODES_OPERATOR_H
#define SNOWY_NODES_OPERATOR_H
#include <string.h>

#include "Node.h"

namespace Snowy
{

enum OperatorType {
    OP_PLUS,
    OP_MINUS,
    OP_MULTIPLY,
    OP_DIVIDE
};

class Operator : public Node
{
public:
    Operator(const char *);

    virtual llvm::Value* compile(CodeGen&) const {
        return NULL;
    }

    OperatorType getOp() const {
        return op;
    }

    virtual void to_sstream(std::ostringstream&) const;

private:
    const static Log log;
    OperatorType op;
};

}
#endif
