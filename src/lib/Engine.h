#ifndef SNOWY_ENGINE_H
#define SNOWY_ENGINE_H

#include <Log.h>

namespace Snowy
{

class Engine
{
public:
    Engine();
    ~Engine();

    static int Parse();

private:
    static const Log log;
};

}

#endif
