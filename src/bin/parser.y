%{
#include <stdio.h>

#define YYDEBUG 1


int yylex();

void yyerror(const char *s) {
  printf("ERROR: %s\n", s);
}

%}

%union {
  char* ident;
  char* program;
  char* string;
};

%token <string> ID
%token <string> INTEGER
%token <token> EQ_OP
%token <token> NUM_OP
%token <string> ENDL
%token <token> COMMA

%type <ident> ident

%start program

%%

program: stmts
       ;

stmts: stmt ENDL { printf("{stmts}"); }
     | stmts stmt ENDL { printf("{stmt}"); }
     ;

stmt: var_decl
    | expr
    ;

var_decl: ident EQ_OP expr { printf("{var_decl}"); }
        ;

ident : ID { printf("{ident %s}", $1); $$ = $1; }

expr: INTEGER { printf("{int exp %s}", $1); }
    | expr NUM_OP expr { printf("{expr num_op expr}"); }
    | ident args { printf("{method call}"); }
    ;

args:
    | expr
    | ident COMMA expr
