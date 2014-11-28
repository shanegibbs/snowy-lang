#include "Expression.h"

#include "Args.h"

using namespace std;

namespace Snowy
{

Args::Args()
{
}

Args::Args(Expression* e)
{
    list.push_back(e);
}

void Args::addArg(Expression* e)
{
    list.push_back(e);
}

void Args::to_sstream(std::ostringstream* s) const
{
    *s << "Args[size=" << list.size();
    if (list.size() > 0) {
        *s << ",";
        for (int i = 0; i < list.size(); i++) {
            if (i != 0) {
                *s << ",";
            }
            *s << "arg" << i << "=[";
            ((Expression*)list[i])->to_sstream(s);
            *s << "]";
        }
    }
    *s << "]";
}

}
