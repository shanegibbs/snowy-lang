#include <glib.h>

#include "DeclareVar.h"

namespace Snowy
{

DeclareVar::DeclareVar(Ident *i, Expression* e)
{
    g_debug("Creating DeclareVar node %d", getId());
    ident = i;
    expr = e;
}

void DeclareVar::to_sstream(std::ostringstream* s) const
{
    g_assert_nonnull(ident);
    g_assert_nonnull(expr);

    *s << "DeclareVar=[ident=[";
    ident->to_sstream(s);
    *s << "] expr=[";
    expr->to_sstream(s);
    *s << "]]";
}

}
