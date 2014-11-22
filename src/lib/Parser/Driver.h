#ifndef SNOWY_DRIVER_HPP
#define SNOWY_DRIVER_HPP

#include <string>
#include <FlexLexer.h>

#include <Parser/Parser.h>

namespace Snowy
{

class Driver
{
public:
  Driver();

  ~Driver();

  void parse();

  void parse(const char *filename);

  int mylex(void*);

  void tick();

private:
  FlexLexer* lexer;
  Snowy::Parser *parser;
};

}
#endif
