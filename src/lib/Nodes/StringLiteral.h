#ifndef SNOWY_NODES_STRING_LITERAL_H
#define SNOWY_NODES_STRING_LITERAL_H

#include <stdlib.h>

#include "Expression.h"

namespace Snowy
{

class Log;

class StringLiteral : public Expression
{
public:
    StringLiteral(const char *str);

    StringLiteral* clone() const
    {
        return new StringLiteral(*this);
    }

    llvm::Value* compile(CodeGen&) const;
    void to_sstream(std::ostringstream&) const;
private:
    static const Log log;
    const char* val;
};

}
#endif

