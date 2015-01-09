#ifndef OPAL_NODES_INT_LITERAL_H
#define OPAL_NODES_INT_LITERAL_H

#include <stdlib.h>

#include "Expression.h"

using namespace std;

namespace Snowy
{

class IntLiteral : public Expression
{
public:
    IntLiteral(const char* str) : val(atoi(str)) {}
    IntLiteral(const string* str) : val(stoi(*str)) {}

    IntLiteral* clone() const
    {
        return new IntLiteral(*this);
    }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(ostringstream&) const;

private:
    static const Log log;
    const int val;
};

}
#endif
