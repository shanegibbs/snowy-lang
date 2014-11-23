#ifndef OPAL_NODES_DECLARE_VAR_H
#define OPAL_NODES_DECLARE_VAR_H

#include "Nodes/Statement.h"
#include "Nodes/Ident.h"
#include "Nodes/Expression.h"

namespace Snowy
{

class DeclareVar : public Statement
{
public:
  DeclareVar(Ident *i, Expression* e) { ident = i; expr = e; }
  ~DeclareVar();

  virtual void to_sstream(std::ostringstream*);

private:
  Ident *ident;
  Expression *expr;
};

}
#endif
