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

const Type* Type::Integer = new Type(shared_ptr<const string>(new string("Integer")));
const Type* Type::String = new Type(shared_ptr<const string>(new string("String")));
const Type* Type::Class = new Type(shared_ptr<const string>(new string("Class")));

Type::Type(const shared_ptr<const string> s) : id(s)
{
    init();
}

Type* Type::clone() const
{
    return new Type(*this);
}

Type::~Type()
{
    // log.debug("Deleting Type(%d) with id '%s'", getNodeId(), id->c_str());
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
