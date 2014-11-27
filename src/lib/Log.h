#include <stdio.h>
#include <stdarg.h>

namespace Snowy
{

class Log
{
public:
    Log(const char* name);
    void debug(const char* format, ...) const;
    void info(const char* format, ...) const;
    void warn(const char* format, ...) const;
    void error(const char* format, ...) const;
    void fatal(const char* format, ...) const;

    static FILE* out;
private:
    const char* name;
    void log(const char* level, const char* format, va_list* args) const;
};

}
