#ifndef OPAL_NODES_DECLARE_VAR_H
#define OPAL_NODES_DECLARE_VAR_H

#include "Statement.h"
#include "Ident.h"
#include "Expression.h"

namespace Snowy
{

class DeclareVar : public Statement
{
public:
  DeclareVar(Ident*, Expression*);

  virtual void to_sstream(std::ostringstream*);

private:
  Ident *ident;
  Expression *expr;
};

}
#endif
