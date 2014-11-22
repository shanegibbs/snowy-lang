#include <stdio.h>

#include "Ident.h"

namespace Snowy
{

Ident::Ident(const char* id)
{
  printf("Ident[%s]\n", id);
}

}
