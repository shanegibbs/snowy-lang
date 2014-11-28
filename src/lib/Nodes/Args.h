#ifndef SNOWY_NODES_ARGS_H
#define SNOWY_NODES_ARGS_H

#include <vector>

#include "Expression.h"

using namespace std;

namespace Snowy
{

class Args : public Node
{
public:
  Args();
  Args(Expression*);

  void addArg(Expression*);

  unsigned int getCount() const
  {
      return list.size();
  }

  Expression* get(unsigned int i) const
  {
      return list[i];
  }

  void to_sstream(std::ostringstream*) const;

private:
  vector<Expression*> list;
};

}
#endif
