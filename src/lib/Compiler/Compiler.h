#include <Node.h>

using namespace llvm;

namespace llvm {
class Module;
class LLVMContext;
class Value;
}

namespace Snowy {

class Log;

class Compiler {
 public:
  Compiler();
  ~Compiler();
  llvm::Module *compile(Node *);

  static void init();

 private:
  static const Log log;

  LLVMContext *context;
  Module *module;
  void write(const llvm::Module *);
  Value *get_exit_value(Value *);
};
}
