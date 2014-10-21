#ifndef NODES_H
#define NODES_H

typedef struct _Ident {
  char* name;
} Ident;

Ident* opal_ident_new(char *name);

#endif
