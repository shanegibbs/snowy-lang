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
    Ident(const char* name);
    Ident(const string* name);
    ~Ident();

    Ident* clone() const {
        return new Ident(*this);
    }

    const string* getName() const {
        return name;
    }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(ostringstream&) const;

private:
    static const Log log;
    void init();
    const string* name;
};

}
#endif
