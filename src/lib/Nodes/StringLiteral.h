#ifndef SNOWY_NODES_STRING_LITERAL_H
#define SNOWY_NODES_STRING_LITERAL_H

#include <stdlib.h>

#include "Expression.h"

namespace Snowy
{

class StringLiteral : public Expression
{
public:
  StringLiteral(const char *str);
  void to_sstream(std::ostringstream*) const;
private:
  const char* val;
};

}
#endif

