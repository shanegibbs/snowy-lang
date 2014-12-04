#include <glib.h>

#include "DeclareVar.h"

namespace Snowy
{

DeclareVar::DeclareVar(Type* t, Ident *i, Expression* e)
{
    g_debug("Creating DeclareVar node %d", getId());
    type = t;
    ident = i;
    expr = e;
}

void DeclareVar::to_sstream(std::ostringstream* s) const
{
    g_assert_nonnull(ident);
    g_assert_nonnull(expr);

    *s << "DeclareVar=[type=[";
    type->to_sstream(s);
    *s << "] ident=[";
    ident->to_sstream(s);
    *s << "] expr=[";
    expr->to_sstream(s);
    *s << "]]";
}

}
