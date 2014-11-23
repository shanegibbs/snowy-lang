#include "Node.h"

Snowy::Node::Node()
{
  next = NULL;
}

const char* Snowy::Node::to_string()
{
  std::ostringstream oss;
  to_sstream(&oss);
  oss << std::endl;

  if (next != NULL) {
    next->to_sstream(&oss);
  }

  const char* oss_out = oss.str().c_str();

  char* cstr = new char[strlen(oss_out) + 1];
  std::strcpy(cstr, oss_out);

  return cstr;
}
