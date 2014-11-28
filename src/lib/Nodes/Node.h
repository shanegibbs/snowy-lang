#ifndef OPAL_NODES_NODE_H
#define OPAL_NODES_NODE_H

#include <iostream>
#include <sstream>
#include <string>

namespace llvm
{
class Value;
}

namespace Snowy
{

class CodeGen;

class Node
{
public:
    Node();

    void setNext(Node *n);

    virtual llvm::Value* compile(CodeGen*) const;

    virtual void to_sstream(std::ostringstream*) const;

    int getId() const
    {
        return id;
    }

    const char* to_string();
    const char* to_program_string();
private:
    Node *next;
    int id;
};

}
#endif

