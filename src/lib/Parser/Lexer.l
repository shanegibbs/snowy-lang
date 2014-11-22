%{
/* C++ string header, for string ops below */
#include <string>
#include "Parser.h"

// %option yyclass="Snowy::Scanner"

const char *mystr;

#define RETURN_STRING(id, desc) mystr = YYText(); return id;
#define RETURN_TOKEN(id, desc) return id;

%}

%option debug
%option noyywrap
%option nodefault

%option c++
%option outfile="Lexer.cc"

INTEGER [0-9]
ID [a-zA-Z][a-zA-Z0-9]*

%%

{ID}                RETURN_STRING(Snowy::Parser::token::ID, "id");
{INTEGER}+          RETURN_STRING(Snowy::Parser::token::INTEGER, "int");
=                   RETURN_TOKEN(Snowy::Parser::token::EQ_OP, "assign");
"+"|"-"|"*"|"/"     RETURN_STRING(Snowy::Parser::token::NUM_OP, "op");
,                   RETURN_TOKEN(Snowy::Parser::token::COMMA, "comma");
\n                  RETURN_TOKEN(Snowy::Parser::token::ENDL, "endl");
[ \t]+
.                   printf("(new char)");

%%

int Xmain( int /* argc */, char** /* argv */ )
{
  FlexLexer* scanner = new yyFlexLexer;
  while(scanner->yylex() != 0) {
    puts(mystr);
  }
  return 0;
}
