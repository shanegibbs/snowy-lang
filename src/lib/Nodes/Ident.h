#ifndef OPAL_NODES_IDENT_H
#define OPAL_NODES_IDENT_H

#include "Expression.h"

namespace Snowy
{

class Ident : public Expression
{
public:
  Ident(const char *name);
//  ~Ident();

  virtual void to_sstream(std::ostringstream*);

private:
  const char *name;
};

}
#endif
