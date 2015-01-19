#ifndef OPAL_NODES_IDENT_H
#define OPAL_NODES_IDENT_H

#include <string>

#include "Expression.h"

using namespace std;

namespace Snowy
{

class Log;
class Type;

class Ident : public Expression
{
public:
    Ident(const char*);
    Ident(const string*);
    Ident(const char*, const Type*);
    Ident(const string*, const Type*);
    ~Ident();

    Ident* clone() const {
        return new Ident(*this);
    }

    const string* getName() const {
        return name;
    }

    NodeType getNodeType() const override { return IDENT; }

    llvm::Value* compile(CodeGen&) const;

    void to_sstream(ostringstream&) const;

private:
    static const Log log;
    void init();
    const string* name;
    const Type* type;
};

}
#endif
