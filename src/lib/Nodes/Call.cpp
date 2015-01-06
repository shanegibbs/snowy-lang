#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "Call.h"

using namespace llvm;
using namespace std;

namespace Snowy
{

const Log Call::log = Log("Call");

Call::Call(const Ident& i, const Args& a) : name(i), args(a)
{
    log.debug("Creating call '%s'", i.getName());
}

void Call::to_sstream(std::ostringstream& s) const
{
    s << "Call=[name=[";
    name.to_sstream(s);
    s << "],args=[";
    args.to_sstream(s);
    s << "]]";
}

Value* Call::compile(CodeGen& gen) const
{
    // LLVMContext* c = &gen->getBuilder()->getContext();

    string fn_name(name.getName());
    Function *fn = gen.getModule()->getFunction(fn_name);
    if (fn == NULL) {
        log.fatal("Function '%s' not found", fn_name.c_str());
    }
    s_assert_notnull(fn);

    vector<Value*> argsV;
    for (unsigned i = 0; i < args.getCount(); i++) {
        Value* argVal = args.get(i).compile(gen);
        s_assert_notnull(argVal);
        argsV.push_back(argVal);
    }

    return gen.getBuilder()->CreateCall(fn, argsV, "fn_call");
}

}
