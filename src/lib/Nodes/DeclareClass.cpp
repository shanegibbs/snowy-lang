#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Argument.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "DeclareClass.h"

using namespace llvm;

namespace Snowy
{

const Log DeclareClass::log = Log("DeclareClass");

DeclareClass::DeclareClass(const Ident* i) : ident(i)
{
    s_assert_notnull(i);
    log.debug("Creating DeclareClass node %s", ident->getName()->c_str());
}

DeclareClass::~DeclareClass()
{
    delete ident;
}

void DeclareClass::to_sstream(std::ostringstream& s) const
{
    s << "DeclareClass=[ident=[";
    ident->to_sstream(s);
    s << "]]";
}

Value* DeclareClass::compile(CodeGen& gen) const
{
    log.debug("Compiling function '%s'", ident->getName()->c_str());
    return NULL;
}

}
