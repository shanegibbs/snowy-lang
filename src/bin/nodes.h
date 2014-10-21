#ifndef NODES_H
#define NODES_H

typedef struct _Ident {
  char* name;
} Ident;

Ident* opal_ident_new(char *name);

typedef struct _IntLiteral {
  int value;
} IntLiteral;

IntLiteral* opal_int_literal_new(char *value);

typedef struct _Expression {
} Expression;

#endif
