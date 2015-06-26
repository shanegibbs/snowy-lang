#ifndef OPAL_NODES_INT_LITERAL_H
#define OPAL_NODES_INT_LITERAL_H

#include <stdlib.h>
#include <memory>

#include "Expression.h"
#include "Type.h"

using namespace std;

namespace Snowy
{

class IntLiteral : public Expression
{
public:
    IntLiteral(const shared_ptr<const string>);

    IntLiteral* clone() const override
    {
        return new IntLiteral(*this);
    }

    const Type* getType() const override final
    {
        return Type::Integer;
    }

    NodeType getNodeType() const override final
    {
        return INT_LITERAL;
    }

    llvm::Value* compile(CodeGen&) const override;

    void to_sstream(ostringstream&) const override;

private:
    static const Log log;
    const int val;
};

}
#endif
