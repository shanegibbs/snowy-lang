#ifndef SNOWY_NODES_TYPE_H
#define SNOWY_NODES_TYPE_H
#include <memory>

#include "Node.h"

using namespace std;

namespace Snowy
{

class Log;

class Type final : public Node
{

public:
    Type(const shared_ptr<const string>);
    ~Type();

    Type* clone() const;

    NodeType getNodeType() const override
    {
        return TYPE;
    }

    const string& getId() const
    {
        return *id;
    }

    llvm::Value* compile(CodeGen&) const
    {
        return NULL;
    }

    void to_sstream(ostringstream&) const;

    static const Type* Class;
    static const Type* Integer;
    static const Type* String;

private:
    void init();

    static const Log log;
    const shared_ptr<const string> id;
};

}
#endif
