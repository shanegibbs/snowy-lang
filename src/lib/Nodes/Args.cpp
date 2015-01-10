#include <SnowyAssert.h>

#include "Expression.h"

#include "Args.h"

using namespace std;

namespace Snowy
{

const Log Args::log = Log("Args");

Args::Args()
{
    log.debug("Created empty Args");
}

Args::~Args()
{
    log.debug("Deleting Args");
    for (const Expression* e : list) {
        delete e;
    }
}

Args::Args(const Expression* e)
{
    log.debug("Created Args with Expression");
    addArg(e);
}

void Args::addArg(const Expression* e)
{
    log.debug("Added Expression to Args list");
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
