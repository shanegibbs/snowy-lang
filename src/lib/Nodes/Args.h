#ifndef SNOWY_NODES_ARGS_H
#define SNOWY_NODES_ARGS_H

#include <vector>

#include "Expression.h"

using namespace std;

namespace Snowy
{

class Args : public Node
{
public:
    Args();
    Args(const Expression*);

    Args* clone() const
    {
        return new Args(*this);
    }

    virtual llvm::Value* compile(CodeGen&) const
    {
        return NULL;
    }

    void addArg(const Expression*);

    unsigned int getCount() const
    {
        return list.size();
    }

    const Expression& get(unsigned int i) const
    {
        return *list[i];
    }

    virtual void to_sstream(std::ostringstream&) const;

private:
    vector<const Expression*> list;
};

}
#endif
