#ifndef OPAL_NODES_IDENT_H
#define OPAL_NODES_IDENT_H

#include "Expression.h"

namespace Snowy
{

class Log;

class Ident : public Expression
{
public:
    Ident(const char *name);

    Ident* clone() const
    {
        return new Ident(*this);
    }

    const char* getName() const
    {
        return name;
    }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(std::ostringstream&) const;

private:
    static const Log log;
    const char *name;
};

}
#endif
