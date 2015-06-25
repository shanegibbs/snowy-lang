#include <stdlib.h>
#include <string>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>
#include <Log.h>
#include <SnowyAssert.h>

#include "Type.h"
#include "StringLiteral.h"

using namespace llvm;
using namespace std;

namespace Snowy
{

const Log StringLiteral::log = Log("StringLiteral");

StringLiteral::StringLiteral(const shared_ptr<const string> str) : val(str)
{
    init();
}

StringLiteral::~StringLiteral()
{
    log.debug("Deleting StringLiteral '%s'", val->c_str());
}

void StringLiteral::init()
{
    s_assert_notnull(val.get());
    s_assert_cmpint(val->length(), >, 0);
    s_assert_cmpint(val->length(), <, 100);

    log.debug("Creating StringLiteral '%s'", val->c_str());
}

const Type* StringLiteral::getType() const
{
    return Type::String;
}

Value* StringLiteral::compile(CodeGen& gen) const
{
    // strip off the quotes
    string val_str(*val);
    string actual = val_str.substr(1, val->length() - 2);

    // unsigned int globalStrIdx = gen->getNextStringLiteralIndex();

    LLVMContext* context = &gen.getBuilder()->getContext();

    // global value
    ArrayType *gv_arr_ty = ArrayType::get(llvm::Type::getInt8Ty(*context), actual.length() + 1);
    StringRef gv_ref(actual.c_str(), actual.length());
    Constant *str_init = ConstantDataArray::getString(*context, gv_ref, true);
    GlobalVariable *str_lit = new GlobalVariable(*gen.getModule(), gv_arr_ty, true, GlobalValue::ExternalLinkage, str_init, "str_lit");

    // pointer to global value
    Constant* eptr_args[2] = {
        ConstantInt::get(*context, APInt(8, 0, false)),
        ConstantInt::get(*context, APInt(8, 0, false))
    };
    ArrayRef<Constant*> eptr_args_ref(eptr_args, 2);
    Constant* gv_ptr = ConstantExpr::getGetElementPtr(str_lit, eptr_args_ref);

    return gv_ptr;
}

void StringLiteral::to_sstream(ostringstream& s) const
{
    s_assert_notnull(val.get());
    s_assert_cmpint(val->length(), >, 0);
    s_assert_cmpint(val->length(), <, 100);

    s << "StringLiteral=[" << *val << "]";
}

}
