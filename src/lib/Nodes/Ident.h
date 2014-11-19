#ifndef OPAL_NODES_IDENT_H
#define OPAL_NODES_IDENT_H

#include "Nodes/Expression.h"

namespace Snowy
{

class Ident : Expression
{
public:
  Ident(const char *name);
  ~Ident();

private:
  char *name;
};

}
#endif
