#ifndef OPAL_NODES_IDENT_H
#define OPAL_NODES_IDENT_H

#include <string>

#include "Expression.h"

using namespace std;

namespace Snowy
{

class Log;
class Type;

class Ident final : public Expression
{
public:
    Ident(const string*);
    Ident(const string*, const Type*);
    ~Ident();

    Ident* clone() const;

    const string* getName() const;

    const Type* getType() const override final;

    void setType(const Type*);

    NodeType getNodeType() const override final { return IDENT; }

    llvm::Value* compile(CodeGen&) const override final;

    void to_sstream(ostringstream&) const override final;

private:
    static const Log log;
    void init();
    const string* name;
    const Type* type;
};

}
#endif
