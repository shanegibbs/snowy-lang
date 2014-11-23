#include <sstream>
#include <FlexLexer.h>

#include <Nodes/Node.h>

#include "Driver.h"

extern const char *mystr;

Snowy::Driver::Driver()
{
  // puts("new Driver");
  lexer = new yyFlexLexer;
  parser = new Snowy::Parser(this);
}

int Snowy::Driver::mylex(Parser::semantic_type *val)
{
  int i = lexer->yylex();
  // printf("Called mylex - %d, %s\n", i, lexer->YYText());
  val->string = lexer->YYText();
  return i;
}

Snowy::Node* Snowy::Driver::parse()
{
  parser->parse();
  return NULL;
}

Snowy::Node* Snowy::Driver::parse(const char *string)
{
  std::stringstream ss;
  ss << string;
  lexer = new yyFlexLexer((std::istream*)&ss);

  parser->parse();
  return NULL;
}

Snowy::Node* Snowy::Driver::parse(FILE *steam)
{
  return NULL;
}
