#include <iostream>
#include <fstream>

#include <Log.h>
#include <Engine.h>

using namespace Snowy;

int main(int argc, char** argv)
{
    Log::setup();
    Engine::init();

    Log log("main");

    ifstream f("run.s");
    if (!f.is_open()) {
        log.fatal("Failed to open default.snow");
    }

    Engine engine;
    if (engine.parse(f)) {
        return engine.exec();
    } else {
        log.fatal("Parsing failed");
    }
}
