#ifndef OPAL_NODES_TUPLE_H
#define OPAL_NODES_TUPLE_H

#include "Expression.h"
#include "Operator.h"

namespace Snowy
{

class Tuple : public Expression
{
public:
    Tuple(Expression*, Operator*, Expression*);
    ~Tuple();

    Tuple* clone() const
    {
        return new Tuple(*this);
    }

    NodeType getNodeType() const override { return TUPLE; }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(std::ostringstream&) const;

private:
    static const Log log;
    const Expression* lhs;
    const Expression* rhs;
    const Operator* op;
};

}
#endif
