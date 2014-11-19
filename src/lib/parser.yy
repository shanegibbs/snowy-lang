%{
#include <stdio.h>

// #include "nodes.h"

#include "Nodes/DeclareVar.h"
#include "Nodes/Expression.h"
#include "Nodes/Ident.h"
#include "Nodes/IntLiteral.h"
#include "Nodes/Node.h"
#include "Nodes/Statement.h"
#include "Nodes/Tuple.h"

#define OPAL_DEBUG 1

int opal_flex_lex();

int opal_bison_lex()
{
  return opal_flex_lex();
}

void yyerror(const char *s) {
  printf("ERROR: %s\n", s);
}

void opal_set_root(Snowy::Node *n);
void opal_add_node(Snowy::Node *last, Snowy::Node *node);

Snowy::NumOp opal_num_op_from_string(char* value)
{
  return Snowy::PLUS;
}

%}

%union {
  Snowy::Node *node;
  Snowy::Ident *ident;
  Snowy::NumOp num_op;
  char* character;
  const char* string;
  Snowy::Expression *expression;
  Snowy::Statement* statement;
  int token;
  Snowy::IntLiteral *int_literal;
  Snowy::DeclareVar *declare_var;
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
%type <declare_var> var_decl
%type <statement> stmt

// %define parse.error verbose

%defines
%define api.prefix {opal_bison_}
%start program

%%

program: node
       ;

node: stmt ENDL { opal_set_root((Snowy::Node*)$1); }
     | node stmt ENDL { printf("{stmt}\n"); }
     | expr ENDL { opal_set_root((Snowy::Node*)$1); }
     | node expr ENDL { $$ = (Snowy::Node*)$2; opal_add_node($1, (Snowy::Node*)$2); }
     ;

stmt: var_decl { $$ = (Snowy::Statement*)$1; }
    ;

var_decl: ident EQ_OP expr { $$ = new Snowy::DeclareVar($1, $3); }
        ;

ident : ID { $$ = new Snowy::Ident($1); }
      ;

num_op: NUM_OP { $$ = opal_num_op_from_string($1); }
      ;

expr: INTEGER { $$ = (Snowy::Expression*) new Snowy::IntLiteral($1); }
    | expr num_op expr { $$ = (Snowy::Expression*) new Snowy::Tuple($1, $2, $3); }
    | ident args { printf("{method call}\n"); }
    ;

args: // blank
    | expr
    | ident COMMA expr
