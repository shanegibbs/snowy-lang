#include <Node.h>

namespace Snowy
{

class Log;

class Compiler
{
public:
    int compile(Node*);

private:
    static const Log log;
};

}
