#include <cstring>

#include "Log.h"

#include "SnowyAssert.h"

using namespace std;
using namespace Snowy;

void snowy_assert_cmpstr(const char* val1, const char* val2, string str1, string str2, string func, string file, int line)
{
    if (strcmp(val1, val2) != 0) {
        Log("assert").fatal("Assertion failed at %s:%d:%s\n\nAssertion was [%s] == [%s]:\n\n'%s'\n'%s'\n", file.c_str(), line, func.c_str(), str1.c_str(), str2.c_str(), val1, val2);
    }
}

void snowy_assert_notnull(void* o, string strO, string func, string file, int line)
{
    if (o == NULL) {
        Log("assert").fatal("Assertion failed at %s:%d\n\nIn function: %s\n\nAssertion was [%s] != NULL\n", file.c_str(), line, func.c_str(), strO.c_str());
    }
}
