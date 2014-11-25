%{
/* C++ string header, for string ops below */
#include <string>

#include "ProgramParser.h"

// %option yyclass="Snowy::Scanner"

typedef Snowy::ProgramParser::token token;
%}

%option debug
%option noyywrap
%option nodefault

%option c++
%option outfile="Lexer.cc"

INTEGER [0-9]
ID [a-zA-Z][a-zA-Z0-9]*

%%

{ID}                return token::ID;
{INTEGER}+          return token::INTEGER;
\"(\\.|[^"])*\"     return token::STRING_LIT;
=                   return token::EQ_OP;
"+"|"-"|"*"|"/"     return token::OP;
,                   return token::COMMA;
\n                  return token::ENDL;
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
