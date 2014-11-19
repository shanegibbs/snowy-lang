#ifndef OPAL_NODES_INT_LITERAL_H
#define OPAL_NODES_INT_LITERAL_H

#include "Nodes/Expression.h"

namespace Snowy
{

class IntLiteral : Expression
{
public:
  IntLiteral(const char *val);
  ~IntLiteral();

private:
  char *val;
};

}
#endif
