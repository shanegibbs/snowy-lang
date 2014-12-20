#ifndef SNOWY_NODES_ARGSDECL_H
#define SNOWY_NODES_ARGSDECL_H

#include <vector>

#include "Node.h"
#include "Type.h"
#include "Ident.h"

using namespace std;

namespace Snowy
{

class ArgsDecl : public Node
{
public:
    ArgsDecl();
    ArgsDecl(Type*, Ident*);

    virtual llvm::Value* compile(CodeGen*) const {
        return NULL;
    }

    void addArgDecl(Type* t, Ident* i);

    unsigned int getCount() const {
        // TODO assert types.size() == idents.size()
        return types.size();
    }

    Type* getType(unsigned int i) const {
        return types[i];
    }

    Ident* getIdent(unsigned int i) const {
        return idents[i];
    }

    virtual void to_sstream(std::ostringstream*) const;

private:
    vector<Type*> types;
    vector<Ident*> idents;
};

}
#endif

