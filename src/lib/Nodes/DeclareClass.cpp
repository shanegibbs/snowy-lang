#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Argument.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "DeclareClass.h"
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
    log.debug("Creating DeclareClass node %s", type->getId()->c_str());
}

DeclareClass::~DeclareClass()
{
    delete type;
}

void DeclareClass::to_sstream(std::ostringstream& s) const
{
    s << "DeclareClass=[type=[";
    type->to_sstream(s);
    s << "]]";
}

Value* DeclareClass::compile(CodeGen& gen) const
{
    log.debug("Compiling function '%s'", type->getId()->c_str());
    return NULL;
}

}
