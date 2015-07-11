#ifndef OPAL_NODES_CALLABLE_H
#define OPAL_NODES_CALLABLE_H

#include "Statement.h"

namespace Snowy {

class Ident;
class ArgsDecl;
class Type;
class Log;

class Callable : public Statement {
 public:
  Callable(const Ident *, const ArgsDecl *, const bool vararg = false);
  ~Callable();

  const string &getName() const;
  const TypePtr getType() const;

 protected:
  const Ident *ident;
  const ArgsDecl *args;
  const bool vararg;

 private:
  static const Log log;
};
}
#endif
