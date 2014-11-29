#include <string>

#include <Engine.h>

int main(int argc, char** argv)
{
    char* log_level = getenv("LOG_LEVEL");
    if (log_level) {
        if (strcmp(log_level, "debug") == 0) {
            Snowy::Log::setLogLevel(Snowy::DEBUG);
        } else if (strcmp(log_level, "info") == 0) {
            Snowy::Log::setLogLevel(Snowy::INFO);
        } else if (strcmp(log_level, "warn") == 0) {
            Snowy::Log::setLogLevel(Snowy::WARN);
        } else if (strcmp(log_level, "error") == 0) {
            Snowy::Log::setLogLevel(Snowy::ERROR);
        }
    }

    Snowy::Engine engine;
    return engine.parse();
}
