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

    static Type create(const char* s) {
        string* str = new string(s);
        Type t(str);
        delete str;
        return t;
    }

    const string& getId() const {
        return id;
    }

    llvm::Value* compile(CodeGen&) const {
        return NULL;
    }

    void to_sstream(ostringstream&) const;

private:
    void init();

    static const Log log;
    const string id;
};

}
#endif
