#ifndef SNOWY_NODES_OPERATOR_H
#define SNOWY_NODES_OPERATOR_H

#include "Node.h"

namespace Snowy
{

class Operator : public Node
{
public:
  Operator(const char *) {}
//  ~Operator();

  virtual void to_sstream(std::ostringstream*);

private:
};

}
#endif
