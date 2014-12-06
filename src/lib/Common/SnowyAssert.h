#ifndef SNOWY_COMMON_ASSERT_H
#define SNOWY_COMMON_ASSERT_H

#include <string>

using namespace std;

void snowy_assert_cmpstr(const char* val1, const char* val2, string str1, string str2, string func, string file, int line);

#define s_assert_cmpstr(s1, s2) do { \
     snowy_assert_cmpstr(s1, s2, #s1, #s2, __PRETTY_FUNCTION__, __FILE__, __LINE__); \
} while (0)

#endif
