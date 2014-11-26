#ifndef SNOWY_NODES_ARGS_H
#define SNOWY_NODES_ARGS_H

#include "Expression.h"

namespace Snowy
{

class Args : public Node
{
public:
  Args();
  Args(Expression*);

  void addArg(Expression*);

  void to_sstream(std::ostringstream*) const;

private:
  int list_size;
  Expression** list;
};

}
#endif
