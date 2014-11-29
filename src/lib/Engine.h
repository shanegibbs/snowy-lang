#ifndef SNOWY_ENGINE_H
#define SNOWY_ENGINE_H

#include <string>

#include <Log.h>

using namespace std;

namespace Snowy
{

class Engine
{
public:
    Engine();
    ~Engine();

    int parse();
    int parse(string code);

    void setStdOut() {
    }

private:
    static const Log log;
};

}

#endif
