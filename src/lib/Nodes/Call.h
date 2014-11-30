#ifndef SNOWY_NODES_CALL_H
#define SNOWY_NODES_CALL_H

#include "Expression.h"
#include "Ident.h"
#include "Args.h"

namespace Snowy
{

class Log;

class Call : public Expression
{
public:
    Call(Ident*, Args*);
    llvm::Value* compile(CodeGen*) const;
    void to_sstream(std::ostringstream*) const;

private:
    static const Log log;
    const Ident* name;
    const Args* args;
};

}
#endif
