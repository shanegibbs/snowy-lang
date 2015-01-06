#ifndef OPAL_NODES_IDENT_H
#define OPAL_NODES_IDENT_H

#include <string>

#include "Expression.h"

using namespace std;

namespace Snowy
{

class Log;

class Ident : public Expression
{
public:
    Ident(const char* n);
    Ident(const string* name);

    Ident* clone() const
    {
        return new Ident(*this);
    }

    const string& getName() const
    {
        return name;
    }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(ostringstream&) const;

private:
    void init();

    static const Log log;
    const string name;
};

}
#endif
