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

  Snowy::Node* parse();

  Snowy::Node* parse(FILE *);

  Snowy::Node* parse(const char *);

  int mylex(Parser::semantic_type *);

  void tick();

  void setRoot(Node *r) { root = r; }

private:
  Node *root;
  FlexLexer* lexer;
  Snowy::Parser *parser;
};

}
#endif
