#include <glib.h>

#include "DeclareVar.h"

void Snowy::DeclareVar::to_sstream(std::ostringstream* s)
{
    g_assert_nonnull(ident);
    g_assert_nonnull(expr);

    *s << "DeclareVar=[ident=[";
    ident->to_sstream(s);
    *s << "] expr=[";
    expr->to_sstream(s);
    *s << "]]";
}
