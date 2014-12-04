#ifndef SNOWY_NODES_TYPE_H
#define SNOWY_NODES_TYPE_H

#include "Node.h"

namespace Snowy
{

class Log;

class Type : public Node
{
public:
    Type(const char *id);

    const char* getId() const
    {
        return id;
    }

    llvm::Value* compile(CodeGen*) const
    {
        return NULL;
    }

    void to_sstream(std::ostringstream*) const;

private:
    static const Log log;
    const char *id;
};

}
#endif
