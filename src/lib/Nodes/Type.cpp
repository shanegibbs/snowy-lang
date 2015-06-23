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
    log.debug("Creating Type(%d) with id '%s'", getNodeId(), s);
    init();
}

Type::Type(const string* s)
{
    char *id_str = (char*)malloc(sizeof(char) * (strlen(s->data()) + 1));
    strcpy(id_str, s->data());
    id = new string(id_str);
    free(id_str);

    init();
}

Type* Type::clone() const
{
    return new Type(*this);
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
