%{
#include <stdio.h>

#include "nodes.h"
#include "parser.h"

int num_lines = 0, num_chars = 0;

// #define RETURN_STRING(id, desc) printf("[%s %s]", desc, yytext); yylval.string = yytext; return id;
// #define RETURN_TOKEN(id, desc) printf("[%s]", desc); return id;

#define RETURN_STRING(id, desc) opal_bison_lval.string = opal_flex_text; return id;
#define RETURN_TOKEN(id, desc) return id;

%}

%option noyywrap
%option always-interactive
%option nounput
%option noinput
%option prefix="opal_flex_"

%option header-file="tokens.h"
%option outfile="tokens.c"

INTEGER [0-9]
ID [a-zA-Z][a-zA-Z0-9]*


%%

{ID}                RETURN_STRING(ID, "id");
{INTEGER}+          RETURN_STRING(INTEGER, "int");
=                   RETURN_TOKEN(EQ_OP, "assign");
"+"|"-"|"*"|"/"     RETURN_STRING(NUM_OP, "op");
,                   RETURN_TOKEN(COMMA, "comma");
\n                  ++num_lines; ++num_chars; RETURN_TOKEN(ENDL, "endl");
[ \t]+
.                   ++num_chars; printf("(new char)");

%%

void exec_lex()
{
  // char* str = "a = 1 + 2 3b\n";
  char* str = "a 1\n";
  yy_scan_string(str);
  yylex();
  printf("\n# of lines = %d, # of chars = %d\n", num_lines, num_chars );
}
