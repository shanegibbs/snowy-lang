%{
#include <stdio.h>

#include "nodes.h"

#define YYDEBUG 1

int yylex();

void yyerror(const char *s) {
  printf("ERROR: %s\n", s);
}

%}

%union {
  Ident* ident;
  char* program;
  char* string;
  int token;
};

%token <string> ID
%token <string> INTEGER
%token <string> ENDL
%token <token> EQ_OP
%token <token> NUM_OP
%token <token> COMMA

%type <ident> ident

%start program

%%

program: stmts
       ;

stmts: stmt ENDL { printf("{stmts}\n"); }
     | stmts stmt ENDL { printf("{stmt}\n"); }
     ;

stmt: var_decl
    | expr
    ;

var_decl: ident EQ_OP expr { printf("{var_decl}\n"); }
        ;

ident : ID { $$ = opal_ident_new($1); }

expr: INTEGER { printf("{int exp %s}\n", $1); }
    | expr NUM_OP expr { printf("{expr num_op expr}\n"); }
    | ident args { printf("{method call}\n"); }
    ;

args: // blank
    | expr
    | ident COMMA expr
