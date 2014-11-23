#include "IntLiteral.h"

void Snowy::IntLiteral::to_sstream(std::ostringstream* s)
{
  *s << "IntLiteral=[" << val << "]";
}
