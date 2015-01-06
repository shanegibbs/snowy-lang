#include <llvm/IR/Constants.h>

#include <CodeGen.h>

#include "IntLiteral.h"

using namespace llvm;

namespace Snowy
{

void IntLiteral::to_sstream(std::ostringstream& s) const
{
    s << "IntLiteral=[" << val << "]";
}

llvm::Value* IntLiteral::compile(CodeGen& gen) const
{
    LLVMContext* context = &gen.getBuilder()->getContext();
    return ConstantInt::get(*context, APInt(32, val, false));
}

}
