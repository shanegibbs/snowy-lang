#ifndef SNOWY_NODES_CALL_H
#define SNOWY_NODES_CALL_H

#include "Expression.h"
#include "Ident.h"
#include "Args.h"

namespace Snowy
{

class Call : public Expression
{
public:
  Call(Ident*, Args*);

  void to_sstream(std::ostringstream*) const;

private:
  const Ident* name;
  const Args* args;
};

}
#endif
