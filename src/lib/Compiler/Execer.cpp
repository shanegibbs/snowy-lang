#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
    buffer = NULL;
    module = m;
}

void Execer::setStdoutBuffer(char* b, int s)
{
    buffer = b;
    buffer_size = s;
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

    const int MAX_LEN = 4096;
    char buffer[MAX_LEN+1] = {0};
    int out_pipe[2];
    int saved_stdout;

    // save stdout
    saved_stdout = dup(STDOUT_FILENO);

    // make pipe
    if( pipe(out_pipe) != 0 ) {
        log.fatal("Failed to create pipe");
    }

    // redirect stdout to pipe
    dup2(out_pipe[1], STDOUT_FILENO);
    close(out_pipe[1]);

    int ret = program_main(2, 4);
    fflush(stdout);

    // read from pipe
    read(out_pipe[0], buffer, MAX_LEN);
    dup2(saved_stdout, STDOUT_FILENO);
    printf("read: %s\n", buffer);

    log.info("main returned %i", ret);

    return ret;
}

}
