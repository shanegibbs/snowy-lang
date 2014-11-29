#include <stdlib.h>
#include <stdio.h>

#include "Log.h"

namespace Snowy
{

FILE* Log::out = stderr;
LogLevel Log::log_level = FATAL;

Log::Log(const char* n)
{
    name = n;
}

void Log::log(LogLevel l, const char* format, va_list* args) const
{
    char* msg = (char*)malloc(4096);
    vsprintf(msg, format, *args);

    const char* level;
    switch (l) {
    case DEBUG:
        level = "DEBUG";
        break;
    case INFO:
        level = "INFO";
        break;
    case WARN:
        level = "WARN";
        break;
    case ERROR:
        level = "ERROR";
        break;
    case FATAL:
        level = "FATAL";
        break;
    };

    fprintf(out, "** %-5s [%s] - %s\n", level, name, msg);
    free(msg);
    fflush(out);
}

void Log::debug(const char* format, ...) const
{
    if (log_level > DEBUG) {
        return;
    }
    va_list args;
    va_start(args, format);
    log(DEBUG, format, &args);
    va_end(args);
}

void Log::info(const char* format, ...) const
{
    if (log_level > INFO) {
        return;
    }
    va_list args;
    va_start(args, format);
    log(INFO, format, &args);
    va_end(args);
}

void Log::warn(const char* format, ...) const
{
    if (log_level > WARN) {
        return;
    }
    va_list args;
    va_start(args, format);
    log(WARN, format, &args);
    va_end(args);
}

void Log::error(const char* format, ...) const
{
    if (log_level > ERROR) {
        return;
    }
    va_list args;
    va_start(args, format);
    log(ERROR, format, &args);
    va_end(args);
}

void Log::fatal(const char* format, ...) const
{
    va_list args;
    va_start(args, format);
    log(FATAL, format, &args);
    va_end(args);
    fprintf(stderr, "** Exiting on FATAL...\n");
    exit(1);
}

}
