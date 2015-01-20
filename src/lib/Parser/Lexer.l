%{
/* C++ string header, for string ops below */
#include <string>

#include <Log.h>
#include "ProgramParser.h"

// %option yyclass="Snowy::Scanner"

typedef Snowy::ProgramParser::token token;

Snowy::Log parser_log("ParserLog");

%}

%option debug
%option noyywrap
%option nodefault
%option yylineno

%option c++
%option outfile="Lexer.cc"

INTEGER [0-9]
ID [a-zA-Z][a-zA-Z0-9]*

%%

do                  return token::DO;
end                 return token::END;
class               return token::CLASS;
def                 return token::DEF;
{ID}                return token::ID;
{INTEGER}+          return token::INTEGER;
\"(\\.|[^"])*\"     return token::STRING_LIT;
=                   return token::EQ_OP;
"+"|"-"|"*"|"/"     return token::OP;
:                   return token::SEPERATOR;
,                   return token::COMMA;
"("                 return token::OPEN_BRACKET;
")"                 return token::CLOSE_BRACKET;
#.*                 return token::COMMENT;
[ \t]+              return token::WHITE_SPACE;
\n                  return token::ENDL;
.                   return token::UNRECOGNIZED_CHAR;

%%
