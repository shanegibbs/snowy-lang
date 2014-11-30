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

class Log;
class CodeGen;

class Node
{
public:
    Node();

    void setNext(Node *n);

    virtual llvm::Value* compile(CodeGen*) const = 0;

    virtual void to_sstream(std::ostringstream*) const = 0;

    int getId() const
    {
        return id;
    }

    Node* getNext() const
    {
        return next;
    }

    const char* to_string();
    const char* to_program_string();
private:
    static const Log log;
    Node *next;
    int id;
};

}
#endif

