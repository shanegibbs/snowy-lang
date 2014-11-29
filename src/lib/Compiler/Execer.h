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
    void setStdoutBuffer(char* buffer, int size);

private:
    static const Log log;
    llvm::Module* module;
    char* buffer;
    unsigned int buffer_size;
};

}

