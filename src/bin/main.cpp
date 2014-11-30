#include <Engine.h>

int main(int argc, char** argv)
{
    Snowy::Log::setup();

    const unsigned int buf_size = 4096;
    char* buf = (char*)malloc(buf_size);

    Snowy::Engine engine;
    engine.setStdoutBuffer(buf, buf_size);

    engine.parse();

    return engine.exec();
}
