#ifndef SNOWY_LOG_H
#define SNOWY_LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <exception>
#include <stdexcept>

namespace Snowy
{

enum LogLevel {
    DEBUG,
    INFO,
    WARN,
    ERROR,
    UI,
    FATAL
};

class FatalLogEvent : public std::runtime_error
{
    public:
    FatalLogEvent() : std::runtime_error("FatalLogEvent") {}
};

class Log
{
public:
    Log(const char* name);
    void debug(const char* format, ...) const;
    void info(const char* format, ...) const;
    void warn(const char* format, ...) const;
    void error(const char* format, ...) const;
    void ui(const char* format, ...) const;
    void fatal(const char* format, ...) const;

    bool isLogLevel(LogLevel l) const
    {
        return l >= log_level;
    }

    static void setLogLevel(LogLevel l)
    {
        log_level = l;
    }

    static void setup();

    static FILE* out;

private:
    void log(LogLevel, const char* format, va_list* args) const;

    const char* name;
    static LogLevel log_level;
    static bool abort_on_fatal;
};

}

#endif
