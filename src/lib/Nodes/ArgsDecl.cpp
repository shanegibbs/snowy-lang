#include "ArgsDecl.h"

using namespace std;

namespace Snowy
{

ArgsDecl::ArgsDecl()
{
}

ArgsDecl::ArgsDecl(const Ident* i)
{
    addIdent(i);
}

ArgsDecl::~ArgsDecl()
{
    for (const Ident* i : idents) {
        delete i;
    }
}

void ArgsDecl::addIdent(const Ident* i)
{
    idents.push_back(i);
}

void ArgsDecl::to_sstream(std::ostringstream& s) const
{
    s << "ArgsDecl[size=" << idents.size();
    if (idents.size() > 0) {
        for (unsigned int i = 0; i < idents.size(); i++) {
            s << " arg" << i << "=[";
            (idents[i])->to_sstream(s);
            s << "]";
        }
    }
    s << "]";
}

}

