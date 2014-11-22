#include "Parser/Driver.h"
#include <FlexLexer.h>

Snowy::Driver::Driver()
{
  puts("new Driver");

  lexer = new yyFlexLexer;
  parser = new Snowy::Parser(this);
}

int Snowy::Driver::mylex(void*)
{
  puts("Called mylex");
  return lexer->yylex();
}

void Snowy::Driver::parse()
{
  parser->parse();
}
