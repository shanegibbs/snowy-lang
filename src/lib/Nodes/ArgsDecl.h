#ifndef SNOWY_NODES_ARGSDECL_H
#define SNOWY_NODES_ARGSDECL_H

#include <vector>

#include <SnowyAssert.h>

#include "Node.h"
#include "Type.h"
#include "Ident.h"

using namespace std;

namespace Snowy {

class ArgsDecl : public Node {
 public:
  ArgsDecl();
  ArgsDecl(const Ident *);
  ~ArgsDecl();

  ArgsDecl *clone() const override { return new ArgsDecl(*this); }

  NodeType getNodeType() const override { return ARGS_DECL; }

  virtual llvm::Value *compile(CodeGen &) const override { return NULL; }

  void addIdent(const Ident *);

  unsigned int size() const { return idents.size(); }

  const Ident &getIdent(unsigned int i) const { return *idents[i]; }

  virtual void to_sstream(std::ostringstream &) const override;

 private:
  static const Log log;
  vector<const Ident *> idents;
};
}
#endif
