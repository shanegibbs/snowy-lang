#include "ArgsDecl.h"

using namespace std;

namespace Snowy
{

ArgsDecl::ArgsDecl()
{
}

ArgsDecl::ArgsDecl(Type* t, Ident* i)
{
    addArgDecl(t, i);
}

void ArgsDecl::addArgDecl(Type* t, Ident* i)
{
    types.push_back(t);
    idents.push_back(i);
}

void ArgsDecl::to_sstream(std::ostringstream* s) const
{
    *s << "ArgsDecl[size=" << types.size();
    if (types.size() > 0) {
        *s << " ";
        for (unsigned int i = 0; i < types.size(); i++) {
            if (i != 0) {
                *s << " ";
            }
            *s << "type" << i << "=[";
            (types[i])->to_sstream(s);
            *s << "]";

            *s << " ident" << i << "=[";
            (idents[i])->to_sstream(s);
            *s << "]";
        }
    }
    *s << "]";
}

}

