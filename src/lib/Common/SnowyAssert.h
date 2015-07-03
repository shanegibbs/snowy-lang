#ifndef SNOWY_COMMON_ASSERT_H
#define SNOWY_COMMON_ASSERT_H

#include <string>

#include <Log.h>

using namespace std;

bool snowy_assert_fail(string str, string func, string file, int line);
void snowy_assert_cmpstr(const char *val1, const char *val2, string str1,
                         string str2, string func, string file, int line);
void snowy_assert_cmpstr(const string &val1, const string &val2, string str1,
                         string str2, string func, string file, int line);
void snowy_assert_cmpstr(const string &val1, const char *val2, string str1,
                         string str2, string func, string file, int line);
void snowy_assert_cmpstr(const char *val1, const string &val2, string str1,
                         string str2, string func, string file, int line);
void snowy_assert_notnull(void *o, string strO, string func, string file,
                          int line);

#define s_assert(x) \
  ((void)(!(x) &&   \
          snowy_assert_fail(#x, __PRETTY_FUNCTION__, __FILE__, __LINE__)))

#define s_assert_cmpstr(s1, s2)                                          \
  do {                                                                   \
    snowy_assert_cmpstr(s1, s2, #s1, #s2, __PRETTY_FUNCTION__, __FILE__, \
                        __LINE__);                                       \
  } while (0)

#define s_assert_notnull(o)                                            \
  do {                                                                 \
    snowy_assert_notnull((void *)o, #o, __PRETTY_FUNCTION__, __FILE__, \
                         __LINE__);                                    \
  } while (0)

#define s_assert_cmpint(n1, cmp, n2)                                           \
  do {                                                                         \
    int _n1 = (n1), _n2 = (n2);                                                \
    if (_n1 cmp _n2)                                                           \
      ;                                                                        \
    else                                                                       \
      Log("assert").fatal(                                                     \
          "Assertion failed at %s:%d:%s\n\nAssertion was [%s] %s [%s]: %d %s " \
          "%d\n",                                                              \
          __FILE__, __LINE__, __PRETTY_FUNCTION__, #n1, #cmp, #n2, _n1, #cmp,  \
          _n2);                                                                \
  } while (0)

#define s_assert_unreachable()                                                 \
  do {                                                                         \
    Log("assert").fatal(                                                       \
        "Assertion failed at %s:%d:%s\n\nAssertion, statement was reached.\n", \
        __FILE__, __LINE__, __PRETTY_FUNCTION__);                              \
  } while (0)

#endif
