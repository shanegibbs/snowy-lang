#include <SnowyAssert.h>

#include "Expression.h"

#include "Args.h"

using namespace std;

namespace Snowy
{

Args::Args()
{
}

Args::Args(const Expression* e)
{
    addArg(e);
}

void Args::addArg(const Expression* e)
{
    s_assert_notnull(e);
    list.push_back(e);
}

void Args::to_sstream(std::ostringstream& s) const
{
    const Expression* e;

    s << "Args[size=" << list.size();
    if (list.size() > 0) {
        s << ",";
        for (unsigned int i = 0; i < list.size(); i++) {
            if (i != 0) {
                s << ",";
            }
            s << "arg" << i << "=[";
            e = list[i];
            e->to_sstream(s);
            s << "]";
        }
    }
    s << "]";
}

}
