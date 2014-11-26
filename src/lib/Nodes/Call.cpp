#include <glib.h>

#include "Call.h"

namespace Snowy
{

Call::Call(Ident* i, Args* a)
{
    name = i;
    args = a;
}

void Call::to_sstream(std::ostringstream* s) const
{
    g_assert_nonnull(name);
    g_assert_nonnull(args);

    *s << "Call=[name=[";
    name->to_sstream(s);
    *s << "],args=[";
    args->to_sstream(s);
    *s << "]]";
}

}
