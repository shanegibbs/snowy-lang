#include <cstring>

#include "Log.h"

#include "SnowyAssert.h"

using namespace std;
using namespace Snowy;

bool snowy_assert_fail(string str, string func, string file, int line) {
  Log("assert").fatal(
      "Assertion failed at %s:%d:%s\n\nAssertion that failed was "
      "[\x1b[33m%s\x1b[0m]\n",
      file.c_str(), line, func.c_str(), str.c_str());
  return false;
}

void snowy_assert_cmpstr(const char *val1, const char *val2, string str1,
                         string str2, string func, string file, int line) {
  if (strcmp(val1, val2) != 0) {
    Log("assert").fatal(
        "Assertion failed at %s:%d:%s\n\nAssertion that failed was "
        "[\x1b[33m%s\x1b[0m] == "
        "[\x1b[33m%s\x1b[0m]:\n\n'%s'\n'%s'\n",
        file.c_str(), line, func.c_str(), str1.c_str(), str2.c_str(), val1,
        val2);
  }
}

void snowy_assert_cmpstr(const string &val1, const string &val2, string str1,
                         string str2, string func, string file, int line) {
  snowy_assert_cmpstr(val1.c_str(), val2.c_str(), str1, str2, func, file, line);
}

void snowy_assert_cmpstr(const string &val1, const char *val2, string str1,
                         string str2, string func, string file, int line) {
  snowy_assert_cmpstr(val1.c_str(), val2, str1, str2, func, file, line);
}

void snowy_assert_cmpstr(const char *val1, const string &val2, string str1,
                         string str2, string func, string file, int line) {
  snowy_assert_cmpstr(val1, val2.c_str(), str1, str2, func, file, line);
}

void snowy_assert_notnull(void *o, string strO, string func, string file,
                          int line) {
  if (o == NULL || o == nullptr) {
    Log("assert").fatal(
        "Assertion failed at %s:%d\n\nIn function: %s\n\nAssertion that failed "
        "was "
        "[\x1b[33m%s\x1b[0m] != NULL\n",
        file.c_str(), line, func.c_str(), strO.c_str());
  }
}
