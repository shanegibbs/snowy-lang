#ifndef SNOWY_DRIVER_HPP
#define SNOWY_DRIVER_HPP

#include <string>

#include <ProgramParser.h>

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

  int mylex(ProgramParser::semantic_type *);

  void error(const char*);

  void tick();

  void setRoot(Node *r) { root = r; }

private:

  Node* exec();

  Node* root;
  FlexLexer* lexer;
  Snowy::ProgramParser *program_parser;
};

}
#endif
