#include "ArgsDecl.h"

using namespace std;

namespace Snowy
{

ArgsDecl::ArgsDecl()
{
}

ArgsDecl::ArgsDecl(const Type* t, const Ident* i)
{
    addArgDecl(t, i);
}

ArgsDecl::~ArgsDecl()
{
    for (const Type* t : types) {
        delete t;
    }
    for (const Ident* i : idents) {
        delete i;
    }
}

void ArgsDecl::addArgDecl(const Type* t, const Ident* i)
{
    types.push_back(t);
    idents.push_back(i);
}

void ArgsDecl::to_sstream(std::ostringstream& s) const
{
    s << "ArgsDecl[size=" << types.size();
    if (types.size() > 0) {
        s << " ";
        for (unsigned int i = 0; i < types.size(); i++) {
            if (i != 0) {
                s << " ";
            }
            s << "type" << i << "=[";
            (types[i])->to_sstream(s);
            s << "]";

            s << " ident" << i << "=[";
            (idents[i])->to_sstream(s);
            s << "]";
        }
    }
    s << "]";
}

}

