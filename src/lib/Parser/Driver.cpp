#include <FlexLexer.h>

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

void Snowy::Driver::parse()
{
  parser->parse();
}
