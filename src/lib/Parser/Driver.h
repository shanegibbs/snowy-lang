#ifndef SNOWY_DRIVER_HPP
#define SNOWY_DRIVER_HPP

#include <string>

#include <Parser/Parser.h>

class FlexLexer;

namespace Snowy
{

class Driver
{
public:
  Driver();

  ~Driver();

  void parse();

  void parse(const char *filename);

  int mylex(Parser::semantic_type *);

  void tick();

private:
  FlexLexer* lexer;
  Snowy::Parser *parser;
};

}
#endif
