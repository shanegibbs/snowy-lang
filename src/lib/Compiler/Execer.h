namespace llvm
{
class Module;
}

namespace Snowy
{

class Log;

class Execer
{
public:
    Execer(llvm::Module*);
    int exec();

private:
    static const Log log;
    llvm::Module* module;
};

}

