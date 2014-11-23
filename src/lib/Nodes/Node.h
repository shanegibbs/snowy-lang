#ifndef OPAL_NODES_NODE_H
#define OPAL_NODES_NODE_H

#include <iostream>
#include <sstream>
#include <string>

namespace Snowy
{

class Node
{
public:
  Node();
  ~Node();

  void setNext(Node *n) { next = n; }

  virtual void to_sstream(std::ostringstream*) {}

  const char* to_string();
private:
  Node *next;
};

}
#endif

