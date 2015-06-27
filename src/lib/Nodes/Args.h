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
    ~Args();

    Args* clone() const override
    {
        return new Args(*this);
    }

    NodeType getNodeType() const override { return ARGS; }

    virtual llvm::Value* compile(CodeGen&) const override
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

    virtual void to_sstream(std::ostringstream&) const override;

private:
    static const Log log;
    vector<const Expression*> list;
};

}
#endif
