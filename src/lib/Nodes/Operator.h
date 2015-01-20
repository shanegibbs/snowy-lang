#ifndef SNOWY_NODES_OPERATOR_H
#define SNOWY_NODES_OPERATOR_H
#include <string.h>

#include "Node.h"

using namespace std;

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
    Operator(const char*);
    Operator(const string*);
    ~Operator();

    Operator* clone() const
    {
        return new Operator(*this);
    }

    NodeType getNodeType() const override { return OPERATOR; }

    virtual llvm::Value* compile(CodeGen&) const {
        return NULL;
    }

    OperatorType getOp() const {
        return op;
    }

    virtual void to_sstream(ostringstream&) const;

private:
    void init(const string& op_str);

    const static Log log;
    OperatorType op;
};

}
#endif
