#ifndef SNOWY_NODES_STRING_LITERAL_H
#define SNOWY_NODES_STRING_LITERAL_H

#include <stdlib.h>

#include "Expression.h"

using namespace std;

namespace Snowy
{

class Log;

class StringLiteral : public Expression
{
public:
    StringLiteral(const char*);
    StringLiteral(const string*);
    ~StringLiteral();

    StringLiteral* clone() const
    {
        return new StringLiteral(*this);
    }

    NodeType getNodeType() const override { return STRING_LITERAL; }

    llvm::Value* compile(CodeGen&) const;
    void to_sstream(ostringstream&) const;
private:
    void init();
    static const Log log;
    const string* val;
};

}
#endif

