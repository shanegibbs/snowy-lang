#include "Callable.h"

#include "Ident.h"
#include "ArgsDecl.h"

using namespace llvm;

namespace Snowy {

  const Log Callable::log = Log("Callable");

  Callable::Callable(const Ident *i, const ArgsDecl *a) : ident(i), args(a) {
    s_assert_notnull(i);
    s_assert_notnull(a);
    log.debug("Creating Callable node %s", ident->getName()->c_str());
  }

  Callable::~Callable() {
    delete ident;
    delete args;
    log.debug("Deleting callable %d", getNodeId());
  }

  const string &Callable::getName() const {
    return *ident->getName();
  }

  const TypePtr Callable::getType() const {
    return ident->getType();
  }

}
