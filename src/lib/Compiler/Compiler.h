#include <Node.h>

using namespace llvm;

namespace llvm
{
class Module;
class LLVMContext;
class Value;
}

namespace Snowy
{

class Log;

class Compiler
{
public:
    Compiler();
    llvm::Module* compile(Node*);

private:
    static const Log log;

    LLVMContext* context;
    void write(const llvm::Module*);
    Value* get_exit_value(Value*);
};

}
