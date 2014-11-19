%{
#include <stdio.h>

#include "Nodes/DeclareVar.h"
#include "Nodes/Expression.h"
#include "Nodes/Ident.h"
#include "Nodes/IntLiteral.h"
#include "Nodes/Node.h"
#include "Nodes/Statement.h"
#include "Nodes/Tuple.h"

#include "parser.hh"

// #define RETURN_STRING(id, desc) printf("[%s %s]", desc, yytext); yylval.string = yytext; return id;
// #define RETURN_TOKEN(id, desc) printf("[%s]", desc); return id;

#define RETURN_STRING(id, desc) opal_bison_lval.string = YYText(); return id;
#define RETURN_TOKEN(id, desc) return id;

// %option prefix="opal_flex_"
// %option yyclass="SnowyScanner"
%}

%option noyywrap
%option always-interactive
%option nounput
%option noinput
%option header-file="tokens.h"
%option outfile="tokens.cc"

%option c++

INTEGER [0-9]
ID [a-zA-Z][a-zA-Z0-9]*


%%

{ID}                RETURN_STRING(ID, "id");
{INTEGER}+          RETURN_STRING(INTEGER, "int");
=                   RETURN_TOKEN(EQ_OP, "assign");
"+"|"-"|"*"|"/"     RETURN_STRING(NUM_OP, "op");
,                   RETURN_TOKEN(COMMA, "comma");
\n                  RETURN_TOKEN(ENDL, "endl");
[ \t]+
.                   printf("(new char)");

%%

