#include <llvm/IR/Constants.h>

#include <Log.h>
#include <SnowyAssert.h>
#include <CodeGen.h>

#include "IntLiteral.h"

using namespace llvm;

namespace Snowy
{

const Log IntLiteral::log = Log("IntLiteral");

IntLiteral::IntLiteral(const shared_ptr<const string> str) : val(stoi(str->c_str()))
{
    s_assert_notnull(str.get());
    log.debug("Creating IntLiteral '%d'", val);
}

void IntLiteral::to_sstream(ostringstream& s) const
{
    s << "IntLiteral=[" << val << "]";
}

llvm::Value* IntLiteral::compile(CodeGen& gen) const
{
    log.debug("Compiling IntLiteral '%d'", val);
    LLVMContext* context = &gen.getBuilder()->getContext();
    return ConstantInt::get(*context, APInt(32, val, false));
}

}
