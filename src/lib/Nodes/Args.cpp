#include "Expression.h"

#include "Args.h"

namespace Snowy
{

Args::Args()
{
    list = NULL;
    list_size = 0;
}

Args::Args(Expression* e)
{
    list = (Expression**)malloc(sizeof(Expression*));
    list[0] = e;
    list_size = 1;
}

void Args::addArg(Expression* e)
{
    puts("[adding arg]");
}

void Args::to_sstream(std::ostringstream* s) const
{
    *s << "Args[size=" << list_size << "]";
    if (list_size > 0) {
        *s << ",";
        for (int i = 0; i < list_size; i++) {
            if (i != 0) {
                *s << ",";
            }
            *s << "arg" << i << "=[";
            ((Expression*)list[i])->to_sstream(s);
            *s << "]";
        }
    }
}

}
