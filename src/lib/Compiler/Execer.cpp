#include <llvm/IR/Module.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>

#include <Log.h>

#include "Execer.h"

using namespace std;
using namespace llvm;

namespace Snowy
{

const Log Execer::log = Log("Execer");

Execer::Execer(Module* m)
{
    module = m;
}

int Execer::exec()
{
    log.debug("Execing");

    std::string ErrStr;
    ExecutionEngine *TheExecutionEngine = EngineBuilder(module).setErrorStr(&ErrStr).create();
    if (!TheExecutionEngine) {
        log.fatal("Could not create ExecutionEngine: %s", ErrStr.c_str());
        exit(1);
    }

    module->setDataLayout(TheExecutionEngine->getDataLayout());

    string fn_name("main");
    Function *main_fn = module->getFunction(fn_name);

    void *main_fn_ptr = TheExecutionEngine->getPointerToFunction(main_fn);
    int (*program_main)(int, int) = (int (*)(int, int))main_fn_ptr;
    int ret = program_main(2, 4);
    log.info("main returned %i", ret);

    return ret;
}

}
