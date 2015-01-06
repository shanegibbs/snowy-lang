#include <stdlib.h>
#include <string>
#include <glib.h>
#include <llvm/IR/GlobalValue.h>
#include <llvm/IR/GlobalVariable.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>
#include <Log.h>
#include "StringLiteral.h"

using namespace llvm;
using namespace std;

namespace Snowy
{

const Log StringLiteral::log = Log("StringLiteral");

StringLiteral::StringLiteral(const char* v)
{
    g_assert_nonnull(v);
    g_assert_cmpint(strlen(v), >, 0);
    g_assert_cmpint(strlen(v), <, 100);

    log.debug("Creating StringLiteral '%s'", v);

    char* new_val = (char*)malloc(strlen(v) + 1);
    strcpy((char*)new_val, v);

    val = (const char*)new_val;
}

Value* StringLiteral::compile(CodeGen& gen) const
{
    // strip off the quotes
    string val_str(val);
    string actual = val_str.substr(1, strlen(val) - 2);

    // unsigned int globalStrIdx = gen->getNextStringLiteralIndex();

    LLVMContext* context = &gen.getBuilder()->getContext();

    // global value
    ArrayType *gv_arr_ty = ArrayType::get(Type::getInt8Ty(*context), actual.length() + 1);
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

void StringLiteral::to_sstream(std::ostringstream& s) const
{
    g_assert_nonnull(val);
    g_assert_cmpint(strlen(val), >, 0);
    g_assert_cmpint(strlen(val), <, 100);

    s << "StringLiteral=[" << val << "]";
}

}
