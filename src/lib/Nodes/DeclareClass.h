#ifndef OPAL_NODES_DECLARE_CLASS_H
#define OPAL_NODES_DECLARE_CLASS_H

#include "Ident.h"
#include "Expression.h"

namespace Snowy
{

class DeclareClass : public Expression
{
public:
    DeclareClass(const Ident*);
    ~DeclareClass();

    DeclareClass* clone() const
    {
        return new DeclareClass(*this);
    }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(std::ostringstream&) const;

private:
    static const Log log;
    const Ident* ident;
};

}
#endif


