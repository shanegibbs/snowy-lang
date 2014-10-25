%{
#include <stdio.h>

#include "nodes.h"

#define OPAL_DEBUG 1

int opal_flex_lex();

int opal_bison_lex()
{
  return opal_flex_lex();
}

void yyerror(const char *s) {
  printf("ERROR: %s\n", s);
}

%}

%union {
  Node *node;
  Ident* ident;
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

%type <node> node
%type <ident> ident
%type <num_op> num_op
%type <expression> expr
%type <declar_var> var_decl
%type <statement> stmt

// %define parse.error verbose

%defines
%define api.prefix {opal_bison_}
%start program

%%

program: node
       ;

node: stmt ENDL { opal_set_root((Node*)$1); }
     | node stmt ENDL { printf("{stmt}\n"); }
     | expr ENDL { opal_set_root((Node*)$1); }
     | node expr ENDL { $$ = (Node*)$2; opal_add_node($1, (Node*)$2); }
     ;

stmt: var_decl { $$ = (Statement*)$1; }
    ;

var_decl: ident EQ_OP expr { $$ = opal_declare_var_new($1, $3); }
        ;

ident : ID { $$ = opal_ident_new($1); }
      ;

num_op: NUM_OP { $$ = opal_num_op_from_string($1); }
      ;

expr: INTEGER { $$ = (Expression*)opal_int_literal_new($1); }
    | expr num_op expr { $$ = (Expression*)opal_tuple_new($1, $2, $3); }
    | ident args { printf("{method call}\n"); }
    ;

args: // blank
    | expr
    | ident COMMA expr
