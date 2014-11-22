#include <FlexLexer.h>

#include "Driver.h"

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