#include <iostream>
#include <fstream>

#include <Log.h>
#include <Engine.h>

using namespace Snowy;

int main(int argc, char **argv) {
  Log::setup();
  Engine::init();

  Log log("main");

  ifstream f("main.s");

  if (!f.is_open()) {
    log.fatal("Failed to open main.s");
  }

  Engine engine;

  if (engine.parse(f)) {
    return engine.exec();
  } else {
    log.fatal("Parsing failed");
  }
}
