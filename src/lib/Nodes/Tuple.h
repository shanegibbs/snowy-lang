#ifndef OPAL_NODES_TUPLE_H
#define OPAL_NODES_TUPLE_H

#include "Expression.h"
#include "Operator.h"

namespace Snowy
{

class Tuple : public Expression
{
public:
  Tuple(Expression *l, Operator *o, Expression *r);

  virtual void to_sstream(std::ostringstream*);

private:
  Expression *lhs;
  Expression *rhs;
  Operator *op;
};

}
#endif
