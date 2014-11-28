#ifndef OPAL_NODES_IDENT_H
#define OPAL_NODES_IDENT_H

#include "Expression.h"

namespace Snowy
{

class Ident : public Expression
{
public:
  Ident(const char *name);

  const char* getName() const
  {
      return name;
  }

  void to_sstream(std::ostringstream*) const;

private:
  const char *name;
};

}
#endif
