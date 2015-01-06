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
    ArgsDecl(Type&, Ident&);

    virtual llvm::Value* compile(CodeGen&) const {
        return NULL;
    }

    void addArgDecl(Type&, Ident&);

    unsigned int getCount() const {
        // TODO assert types.size() == idents.size()
        return types.size();
    }

    const Type& getType(unsigned int i) const {
        return *types[i];
    }

    const Ident& getIdent(unsigned int i) const {
        return *idents[i];
    }

    virtual void to_sstream(std::ostringstream&) const;

private:
    vector<const Type*> types;
    vector<const Ident*> idents;
};

}
#endif

