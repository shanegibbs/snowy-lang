#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#include <SnowyAssert.h>
#include <Log.h>

#include "Type.h"

using namespace std;

namespace Snowy
{

const Log Type::log = Log("Type");
const Type* Type::Integer = new Type("Integer");
const Type* Type::String = new Type("String");
const Type* Type::Class = new Type("Class");

Type::Type(const char* s) : id(new string(s))
{
    init();
}

Type::Type(const string* s) : id(s)
{
    init();
}

Type::~Type()
{
    log.debug("Deleting Type(%d) with id '%s'", getNodeId(), id->c_str());
    delete id;
}

void Type::init()
{
    log.debug("Creating Type '%s'", id->c_str());

    s_assert_cmpint(id->length(), >, 0);
    s_assert_cmpint(id->length(), <, 100);
}

void Type::to_sstream(std::ostringstream& s) const
{
    s_assert_cmpint(id->length(), >, 0);
    s_assert_cmpint(id->length(), <, 100);

    s << "Type[" << *id << "]";
}

}
