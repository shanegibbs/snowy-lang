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
  char* ident;
  NumOp num_op;
  char* character;
  char* string;
  Expression* expression;
  Statement* statement;
  int token;
  IntLiteral *int_literal;
  DeclarVar *declar_var;
};

%token <string> ID
%token <string> INTEGER
%token <string> ENDL
%token <token> EQ_OP
%token <character> NUM_OP
%token <token> COMMA

%type <ident> ident
%type <num_op> num_op
%type <expression> expr
%type <declar_var> var_decl
%type <statement> stmt

%start program

%%

program: node
       ;

node: stmt ENDL { root = $1; printf("{first stmt}\n"); }
     | stmts stmt ENDL { printf("{stmt}\n"); }
     ;

stmt: var_decl { $$ = $1->parent; }
    | expr
    ;

var_decl: ident EQ_OP expr { $$ = opal_declare_var_new($1, $3); }
        ;

ident : ID { $$ = opal_ident_new($1); }
      ;

num_op: NUM_OP { $$ = opal_num_op_from_string($1); }
      ;

expr: INTEGER { $$ = opal_int_literal_new($1)->parent; }
    | expr num_op expr { $$ = opal_tuple_new($1, $2, $3)->parent; }
    | ident args { printf("{method call}\n"); }
    ;

args: // blank
    | expr
    | ident COMMA expr
