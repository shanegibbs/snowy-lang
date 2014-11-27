#include <Node.h>

namespace Snowy
{

class Log;

class Compiler
{
public:
    void compile(Node*);

private:
    static const Log log;
};

}
