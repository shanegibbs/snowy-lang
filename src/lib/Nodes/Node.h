#ifndef OPAL_NODES_NODE_H
#define OPAL_NODES_NODE_H

#include <iostream>
#include <sstream>
#include <string>

class llvm::IRBuilder;

namespace Snowy
{

class Node
{
public:
  Node();

  void setNext(Node *n);

  virtual void to_sstream(std::ostringstream*) const;
  virtual void compile(llvm::IRBuilder<>*) const;

  int getId() { return id; }

  const char* to_string();
  const char* to_program_string();
private:
  Node *next;
  int id;
};

}
#endif

