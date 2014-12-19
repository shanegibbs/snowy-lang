#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "DeclareFunc.h"

using namespace llvm;

namespace Snowy
{

const Log DeclareFunc::log = Log("DeclareFunc");

DeclareFunc::DeclareFunc(Type* t, Ident *i, ArgsDecl* a, Node* b)
{
    log.debug("Creating DeclarerFunc node %d", getId());
    type = t;
    ident = i;
    args = a;
    block = b;
}

void DeclareFunc::to_sstream(std::ostringstream* s) const
{
    s_assert_notnull(type);
    s_assert_notnull(ident);
    s_assert_notnull(args);

    *s << "DeclareFunc=[type=[";
    type->to_sstream(s);
    *s << "] ident=[";
    ident->to_sstream(s);
    *s << "] args=[";
    args->to_sstream(s);
    *s << "] block=[";
    if (block == NULL) {
        *s << "NULL";
    } else {
        Node* current = block;
        while (current != NULL) {
            current->to_sstream(s);
            *s << endl;
            current = current->getNext();
        }
    }
    *s << "]]";
}

Value* DeclareFunc::compile(CodeGen* gen) const
{
    return NULL;
}

}
