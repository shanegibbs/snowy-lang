#ifndef SNOWY_NODES_TYPE_H
#define SNOWY_NODES_TYPE_H

#include "Node.h"

using namespace std;

namespace Snowy
{

class Log;

class Type : public Node
{
public:
    Type(const char* s);
    Type(const string* s);
    ~Type();

    Type* clone() const
    {
        return new Type(*this);
    }

    const string* getId() const {
        return id;
    }

    llvm::Value* compile(CodeGen&) const {
        return NULL;
    }

    void to_sstream(ostringstream&) const;

private:
    void init();

    static const Log log;
    const string* id;
};

}
#endif
