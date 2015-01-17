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

do                  return token::DO;
end                 return token::END;
{ID}                return token::ID;
{INTEGER}+          return token::INTEGER;
\"(\\.|[^"])*\"     return token::STRING_LIT;
=                   return token::EQ_OP;
"+"|"-"|"*"|"/"     return token::OP;
,                   return token::COMMA;
"("                 return token::OPEN_BRACKET;
")"                 return token::CLOSE_BRACKET;
#.*
\n                  return token::ENDL;
[ \t\n]+
.                   printf("(new char)");

%%
