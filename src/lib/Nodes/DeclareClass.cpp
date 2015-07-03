#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Argument.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "DeclareClass.h"
#include "FuncDef.h"
#include "DeclareVar.h"
#include "Type.h"

using namespace llvm;

namespace Snowy {

const Log DeclareClass::log = Log("DeclareClass");

DeclareClass::DeclareClass() {
  type = nullptr;
  log.debug("Creating DeclareClass");
}

DeclareClass::DeclareClass(TypePtr t) : type(t) {
  s_assert(t);
  log.debug("Creating DeclareClass node %s", type->getId().c_str());
}

DeclareClass::~DeclareClass() {
  log.debug("Deleting DeclareClass '%s'", type->getId().c_str());

  for (DeclareVar *v : vars) {
    delete v;
  }

  vars.clear();

  for (FuncDef *f : funcs) {
    delete f;
  }

  funcs.clear();
}

DeclareClass *DeclareClass::clone() const { return new DeclareClass(*this); }

NodeType DeclareClass::getNodeType() const { return DECLARE_CLASS; }

void DeclareClass::setType(const TypePtr t) {
  s_assert(t);
  log.debug("Setting type of DeclareClass to %s", t->getId().c_str());
  type = t;
}

void DeclareClass::addVarDecl(DeclareVar *v) {
  DeclareVar *obj = dynamic_cast<DeclareVar *>(v);
  vars.push_back(obj);
}

void DeclareClass::addFuncDecl(FuncDef *v) { funcs.push_back(v); }

vector<DeclareVar *> &DeclareClass::getVars() { return vars; }

vector<FuncDef *> &DeclareClass::getFuncs() { return funcs; }

const TypePtr DeclareClass::getType() const {
  return TypePtr(new Type(shared_ptr<string>(new string("Class"))));
}

const Type &DeclareClass::getClassType() const {
  s_assert(type);
  return *type;
}

void DeclareClass::to_sstream(std::ostringstream &s) const {
  s_assert(type);
  s << "DeclareClass=[type=[";
  type->to_sstream(s);
  s << "]]";
}

Value *DeclareClass::compile(CodeGen &gen) const {
  log.debug("Compiling function '%s'", type->getId().c_str());
  return NULL;
}
}
