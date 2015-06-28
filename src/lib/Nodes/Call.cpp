#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "Call.h"
#include "Args.h"
#include "DeclareFunc.h"

using namespace llvm;
using namespace std;

namespace Snowy
{

const Log Call::log = Log("Call");

Call::Call(const DeclareFunc *f, const Args* a) : func(f), args(a)
{
    s_assert_notnull(func);
    s_assert_notnull(args);
    log.debug("Creating call to '%s'", func->getName().c_str());
}

Call::~Call()
{
    // log.debug("Deleting call %d", getNodeId());
    delete args;
}

Call* Call::clone() const
{
    return new Call(*this);
}

const Type* Call::getType() const
{
    return func->getType();
}

void Call::to_sstream(std::ostringstream& s) const
{
    s << "Call=[name=[";
    func->to_sstream(s);
    s << "],args=[";
    args->to_sstream(s);
    s << "]]";
}

Value* Call::compile(CodeGen& gen) const
{
    log.debug("Compiling call to '%s'", func->getName().c_str());
    // LLVMContext* c = &gen->getBuilder()->getContext();

    string fn_name(func->getName());
    Function *fn = gen.getModule()->getFunction(fn_name);
    if (fn == NULL) {
        log.fatal("Function '%s' not found", fn_name.c_str());
    }
    s_assert_notnull(fn);

    vector<Value*> argsV;
    for (unsigned i = 0; i < args->getCount(); i++) {
        Value* argVal = args->get(i).compile(gen);
        s_assert_notnull(argVal);
        argsV.push_back(argVal);
    }

    return gen.getBuilder()->CreateCall(fn, argsV, "fn_call");
}

}
