#ifndef OPAL_NODES_INT_LITERAL_H
#define OPAL_NODES_INT_LITERAL_H

#include <stdlib.h>

#include <Nodes/Expression.h>

namespace Snowy
{

class IntLiteral : public Expression
{
public:
  IntLiteral(const char *str) { val = atoi(str); }
  ~IntLiteral();
  virtual void to_sstream(std::ostringstream*);
private:
  int val;
};

}
#endif
