#ifndef OPAL_NODES_INT_LITERAL_H
#define OPAL_NODES_INT_LITERAL_H

#include <stdlib.h>

#include "Expression.h"

namespace Snowy
{

class IntLiteral : public Expression
{
public:
    IntLiteral(const char *str)
    {
        val = atoi(str);
    }

    llvm::Value* compile(CodeGen*) const
    {
        return NULL;
    }

    void to_sstream(std::ostringstream*) const;

private:
    int val;
};

}
#endif
