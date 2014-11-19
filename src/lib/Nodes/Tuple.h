#ifndef OPAL_NODES_TUPLE_H
#define OPAL_NODES_TUPLE_H

#include "Nodes/Expression.h"

namespace Snowy
{

class Tuple : Expression
{
public:
  Tuple(Expression *lhs, NumOp num_op, Expression *rhs);
  ~Tuple();

private:
};

}
#endif
