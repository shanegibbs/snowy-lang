#include <stdlib.h>
#include <stdio.h>

#include "Log.h"

namespace Snowy
{

FILE* Log::out = stderr;

Log::Log(const char* n)
{
    name = n;
}

void Log::log(const char* level, const char* format, va_list* args) const
{
    char* msg = (char*)malloc(4096);
    vsprintf(msg, format, *args);

    fprintf(out, "** %-5s [%s] - %s\n", level, name, msg);
    free(msg);
}

void Log::debug(const char* format, ...) const
{
    va_list args;
    va_start(args, format);
    log("DEBUG", format, &args);
    va_end(args);
}

void Log::info(const char* format, ...) const
{
    va_list args;
    va_start(args, format);
    log("INFO", format, &args);
    va_end(args);
}

void Log::warn(const char* format, ...) const
{
    va_list args;
    va_start(args, format);
    log("WARN", format, &args);
    va_end(args);
}

void Log::error(const char* format, ...) const
{
    va_list args;
    va_start(args, format);
    log("ERROR", format, &args);
    va_end(args);
}

void Log::fatal(const char* format, ...) const
{
    va_list args;
    va_start(args, format);
    log("FATAL", format, &args);
    va_end(args);
    fprintf(stderr, "** Exiting on FATAL...\n");
    exit(1);
}

}
