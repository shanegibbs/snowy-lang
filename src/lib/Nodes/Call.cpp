#include <glib.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGen.h>

#include "Call.h"

using namespace llvm;
using namespace std;

namespace Snowy
{

Call::Call(Ident* i, Args* a)
{
    name = i;
    args = a;
}

void Call::to_sstream(std::ostringstream* s) const
{
    g_assert_nonnull(name);
    g_assert_nonnull(args);

    *s << "Call=[name=[";
    name->to_sstream(s);
    *s << "],args=[";
    args->to_sstream(s);
    *s << "]]";
}

Value* Call::compile(CodeGen* gen) const
{
    // LLVMContext* c = &gen->getBuilder()->getContext();

    string fn_name(name->getName());
    Function *fn = gen->getModule()->getFunction(fn_name);

    vector<Value*> argsV;
    for (unsigned i = 0; i < args->getCount(); i++) {
        Value* argVal = args->get(i)->compile(gen);
        g_assert_nonnull(argVal);
        argsV.push_back(argVal);
    }

    return gen->getBuilder()->CreateCall(fn, argsV, "my_fn_call");
}

}
