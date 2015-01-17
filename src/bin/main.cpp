#include <iostream>
#include <fstream>

#include <Log.h>
#include <Engine.h>

using namespace Snowy;

int main(int argc, char** argv)
{
    Log::setup();
    Log log("main");

    Engine::init();

    Engine engine;

    int parse_result = 0;

    if (argc == 2) {
        ifstream f(argv[1]);
        if (!f.is_open()) {
            log.fatal("Failed to open '%s'", argv[1]);
        }
        parse_result = engine.parse(f);
    } else {
        parse_result = engine.parse();
    }

    if (!parse_result) {
        log.fatal("Parsing failed");
    }

    return engine.exec();
}
