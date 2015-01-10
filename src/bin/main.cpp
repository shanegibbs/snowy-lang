#include <Log.h>
#include <Engine.h>

using namespace Snowy;

int main(int argc, char** argv)
{
    Log::setup();
    Engine::init();

    Engine engine;
    engine.parse();
    return engine.exec();
}
