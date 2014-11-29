#include <Node.h>

namespace llvm
{
class Module;
}

namespace Snowy
{

class Log;

class Compiler
{
public:
    llvm::Module* compile(Node*);

private:
    static const Log log;

    void write(const llvm::Module*);
};

}
