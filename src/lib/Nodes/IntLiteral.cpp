#include <llvm/IR/Constants.h>

#include <Log.h>
#include <SnowyAssert.h>
#include <CodeGen.h>

#include "IntLiteral.h"

using namespace llvm;

namespace Snowy
{

const Log IntLiteral::log = Log("IntLiteral");

IntLiteral::IntLiteral(const char* str) : val(atoi(str))
{
    s_assert_notnull(str);
    log.debug("Creating IntLiteral '%d'", val);
}

IntLiteral::IntLiteral(const string* str) : val(stoi(*str))
{
    s_assert_notnull(str);
    log.debug("Creating IntLiteral '%d'", val);
    delete str;
}

void IntLiteral::to_sstream(ostringstream& s) const
{
    s << "IntLiteral=[" << val << "]";
}

llvm::Value* IntLiteral::compile(CodeGen& gen) const
{
    LLVMContext* context = &gen.getBuilder()->getContext();
    return ConstantInt::get(*context, APInt(32, val, false));
}

}
