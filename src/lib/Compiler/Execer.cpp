#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include <llvm/IR/Module.h>
#include <llvm/IR/DataLayout.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ManagedStatic.h>

#include <Log.h>
#include <SnowyAssert.h>

#include "Execer.h"

using namespace std;
using namespace llvm;

namespace Snowy {

const Log Execer::log = Log("Execer");

Execer::Execer() { buffer = NULL; }

void Execer::setStdoutBuffer(char *b, int s) {
  log.debug("Setting stdout buffer");
  buffer = b;
  buffer_size = s;
}

int Execer::exec(Module *module) {
  log.debug("Execing");

  std::string ErrStr;
  // ExecutionEngine takes ownership of module from here
  // when EE is deleted, so is module.
  ExecutionEngine *TheExecutionEngine =
      EngineBuilder(unique_ptr<Module>(module)).setErrorStr(&ErrStr).create();

  if (!TheExecutionEngine) {
    log.fatal("Could not create ExecutionEngine: %s", ErrStr.c_str());
    exit(1);
  }

  TheExecutionEngine->finalizeObject();
  TheExecutionEngine->runStaticConstructorsDestructors(false);

  // module->setDataLayout(TheExecutionEngine->getDataLayout()->getStringRepresentation());

  string fn_name("main");
  Function *main_fn = module->getFunction(fn_name);

  void *main_fn_ptr = TheExecutionEngine->getPointerToFunction(main_fn);
  int (*program_main)(int, int) = (int (*)(int, int))main_fn_ptr;

  int out_pipe[2];
  int saved_stdout = 0;

  if (buffer != NULL) {
    s_assert_notnull(buffer);

    // save stdout
    saved_stdout = dup(STDOUT_FILENO);

    // make pipe
    if (pipe(out_pipe) != 0) {
      log.fatal("Failed to create pipe");
    }

    // redirect stdout to pipe
    dup2(out_pipe[1], STDOUT_FILENO);
    close(out_pipe[1]);
  }

  int ret = program_main(2, 4);
  fflush(stdout);

  TheExecutionEngine->runStaticConstructorsDestructors(true);

  delete TheExecutionEngine;

  if (buffer != NULL) {
    // read from pipe
    fcntl(out_pipe[0], F_SETFL, O_NONBLOCK);
    ssize_t r = read(out_pipe[0], buffer, buffer_size);

    if (r != -1) {
      buffer[r] = 0;
    } else {
      buffer[0] = 0;
    }

    // swap back real stdout
    dup2(saved_stdout, STDOUT_FILENO);

    log.debug("Read %d bytes", r);
    log.debug("stdout was: '%s'\n", buffer);
  }

  log.info("main returned %i", ret);

  return ret;
}

void Execer::shutdown() { llvm_shutdown(); }
}
