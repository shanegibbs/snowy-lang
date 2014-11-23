#include <stdio.h>

#include "Tuple.h"

namespace Snowy
{

Tuple::Tuple(Expression *l, Operator *o, Expression *r)
{
    lhs = l;
    rhs = r;
    op = o;
    printf("Tuple[]\n");
}

void Snowy::Tuple::to_sstream(std::ostringstream* s)
{
    *s << "Tuple=[lhs=[";
    lhs->to_sstream(s);
    *s << "] op=[";
    op->to_sstream(s);
    *s << "] rhs=[";
    rhs->to_sstream(s);
    *s << "]]";
}

}
