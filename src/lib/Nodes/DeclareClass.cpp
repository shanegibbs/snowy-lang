#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Argument.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "DeclareClass.h"
#include "DeclareFunc.h"
#include "Type.h"

using namespace llvm;

namespace Snowy
{

const Log DeclareClass::log = Log("DeclareClass");

DeclareClass::DeclareClass()
{
    type = nullptr;
    log.debug("Creating DeclareClass");
}

DeclareClass::DeclareClass(Type* t) : type(t)
{
    s_assert_notnull(t);
    log.debug("Creating DeclareClass node %s", type->getId().c_str());
}

DeclareClass::~DeclareClass()
{
    log.debug("Deleting DeclareClass '%s'", type->getId().c_str());

    delete type;
    vars.clear();

    for (DeclareFunc *f : funcs) {
        delete f;
    }
    funcs.clear();
}

DeclareClass* DeclareClass::clone() const
{
    return new DeclareClass(*this);
}

NodeType DeclareClass::getNodeType() const
{
    return DECLARE_CLASS;
}

void DeclareClass::setType(const Type* t)
{
    s_assert_notnull(t);
    log.debug("Setting type of DeclareClass to %s", t->getId().c_str());
    type = t;
}

void DeclareClass::addVarDecl(DeclareVar* v)
{
    vars.push_back(v);
}

void DeclareClass::addFuncDecl(DeclareFunc* v)
{
    funcs.push_back(v);
}

vector<DeclareVar*>& DeclareClass::getVars()
{
    return vars;
}

vector<DeclareFunc*>& DeclareClass::getFuncs()
{
    return funcs;
}

const Type* DeclareClass::getType() const
{
    return Type::Class;
}

const Type& DeclareClass::getClassType() const
{
    s_assert_notnull(type);
    return *type;
}

void DeclareClass::to_sstream(std::ostringstream& s) const
{
    s_assert_notnull(type);
    s << "DeclareClass=[type=[";
    type->to_sstream(s);
    s << "]]";
}

Value* DeclareClass::compile(CodeGen& gen) const
{
    log.debug("Compiling function '%s'", type->getId().c_str());
    return NULL;
}

}
