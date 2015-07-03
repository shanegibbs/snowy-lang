#ifndef SNOWY_PARSER_HPP
#define SNOWY_PARSER_HPP

#include <istream>
#include <string>

namespace Snowy {

class Log;
class Driver;
class Node;

class Parser {
 public:
  Parser();
  ~Parser();

  Node *parse();
  Node *parse(std::istream &);

 private:
  static const Log log;
  Driver *driver;
};
}
#endif
