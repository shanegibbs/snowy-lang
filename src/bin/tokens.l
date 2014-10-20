%{
#include <stdio.h>

#include "parser.h"

int num_lines = 0, num_chars = 0;

%}

%option noyywrap
%option always-interactive
%option nounput
%option noinput

INTEGER [0-9]
ID [a-zA-Z][a-zA-Z0-9]*

%%

{ID}                printf("[id %s]", yytext); yylval.string = yytext; return ID;
{INTEGER}+          printf("[int %d]", atoi(yytext)); yylval.string = yytext; return INTEGER;
=                   printf("[assign]"); return EQ_OP;
"+"|"-"|"*"|"/"     printf("[operator %s]", yytext); return NUM_OP;
,                   printf("[comma]"); return COMMA;
\n                  ++num_lines; ++num_chars; printf("[new line]\n"); return ENDL;
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
