#include <stdio.h>

#include "Tuple.h"

namespace Snowy
{

Tuple::Tuple(Expression *l, NumOp o, Expression *r)
{
  lhs = l;
  rhs = r;
  op = o;
  printf("Tuple[]\n");
}

}
