#ifndef OPAL_NODES_NODE_H
#define OPAL_NODES_NODE_H

namespace Snowy
{

class Node
{
public:
  Node() {}
  ~Node();
};

typedef enum
{
  NUM_OP_NULL,
  PLUS,
  MINUS,
  MULTIPLY,
  DIVIDE
} NumOp;

}
#endif

