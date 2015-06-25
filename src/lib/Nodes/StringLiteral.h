#ifndef SNOWY_NODES_STRING_LITERAL_H
#define SNOWY_NODES_STRING_LITERAL_H

#include <stdlib.h>

#include "Expression.h"

using namespace std;

namespace Snowy
{

class Log;
class Type;

class StringLiteral final : public Expression
{
public:
    StringLiteral(const string*);
    ~StringLiteral();

    StringLiteral* clone() const override final
    {
        return new StringLiteral(*this);
    }

    NodeType getNodeType() const override { return STRING_LITERAL; }

    const Type* getType() const override final;

    llvm::Value* compile(CodeGen&) const override final;
    void to_sstream(ostringstream&) const override final;

private:
    void init();
    static const Log log;
    const string* val;
};

}
#endif
