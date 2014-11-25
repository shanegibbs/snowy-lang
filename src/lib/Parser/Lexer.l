%{
/* C++ string header, for string ops below */
#include <string>

#include "Parser.h"

// %option yyclass="Snowy::Scanner"

%}

%option debug
%option noyywrap
%option nodefault

%option c++
%option outfile="Lexer.cc"

INTEGER [0-9]
ID [a-zA-Z][a-zA-Z0-9]*

%%

{ID}                return Snowy::Parser::token::ID;
{INTEGER}+          return Snowy::Parser::token::INTEGER;
\"(\\.|[^"])*\"     return Snowy::Parser::token::STRING_LIT;
=                   return Snowy::Parser::token::EQ_OP;
"+"|"-"|"*"|"/"     return Snowy::Parser::token::OP;
,                   return Snowy::Parser::token::COMMA;
\n                  return Snowy::Parser::token::ENDL;
[ \t]+
.                   printf("(new char)");

%%

int Xmain( int /* argc */, char** /* argv */ )
{
  FlexLexer* scanner = new yyFlexLexer;
  while(scanner->yylex() != 0) {
    puts(scanner->YYText());
  }
  return 0;
}
