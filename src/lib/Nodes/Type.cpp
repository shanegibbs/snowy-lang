#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include <SnowyAssert.h>
#include <Log.h>

#include "Type.h"

namespace Snowy
{

const Log Type::log = Log("Type");

Type::Type(const char* n)
{
    log.debug("Creating Type with id '%s'", n);

    s_assert_notnull(n);
    s_assert_cmpint(strlen(n), >, 0);
    s_assert_cmpint(strlen(n), <, 100);

    char* new_id = (char*) malloc(strlen(n) + 1);
    strcpy(new_id, n);
    id = new_id;
}

void Type::to_sstream(std::ostringstream& s) const
{
    s_assert_notnull(id);
    s_assert_cmpint(strlen(id), >, 0);
    s_assert_cmpint(strlen(id), <, 100);

    s << "Type[" << id << "]";
}

}
