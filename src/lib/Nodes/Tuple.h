#ifndef OPAL_NODES_TUPLE_H
#define OPAL_NODES_TUPLE_H

#include <Nodes/Expression.h>

namespace Snowy
{

class Tuple : public Expression
{
public:
  Tuple(Expression *l, NumOp o, Expression *r);
  ~Tuple();

private:
  Expression *lhs;
  Expression *rhs;
  NumOp op;
};

}
#endif
