#include "IntLiteral.h"

void Snowy::IntLiteral::to_sstream(std::ostringstream* s) const
{
  *s << "IntLiteral=[" << val << "]";
}
