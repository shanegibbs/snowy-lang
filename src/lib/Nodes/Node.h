#ifndef OPAL_NODES_NODE_H
#define OPAL_NODES_NODE_H

#include <iostream>
#include <sstream>
#include <string>

#include "NodeType.h"

namespace llvm {
  class Value;
}

namespace Snowy {

  class Log;
  class CodeGen;

  class Node {
   public:
    Node();
    virtual ~Node();
    virtual Node *clone() const = 0;

    void setNext(Node *n);

    virtual llvm::Value *compile(CodeGen &) const = 0;

    virtual void to_sstream(std::ostringstream &) const = 0;

    virtual NodeType getNodeType() const = 0;

    bool isNodeType(NodeType t) const {
      return t == getNodeType();
    }

    int getNodeId() const {
      return node_id;
    }

    Node *getFirst() const;

    Node *getNext() const {
      return next;
    }

    const char *to_string() const;
    const std::string to_program_string() const;
   private:
    static const Log log;
    Node *first;
    Node *next;
    const int node_id;
  };

}
#endif

