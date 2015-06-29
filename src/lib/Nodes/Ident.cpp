#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/IRBuilder.h>

#include <Log.h>
#include <SnowyAssert.h>
#include <CodeGen.h>

#include "Ident.h"
#include "Type.h"

using namespace llvm;

namespace Snowy
{

const Log Ident::log = Log("Ident");

void Ident::init()
{
    s_assert_notnull(name.get());
    s_assert_cmpint(name->length(), >, 0);
    s_assert_cmpint(name->length(), <, 100);
}

Ident::Ident(const shared_ptr<const string> s) : name(s), type(nullptr)
{
    log.debug("Creating Identity '%s'", name->c_str());
    init();
}

Ident::Ident(const shared_ptr<const string> s, const TypePtr t) : name(s), type(t)
{
  s_assert(type);
    log.debug("Creating Identity '%s' with type '%s'", name->c_str(), type->getId().c_str());
    init();
}

Ident::~Ident()
{
    // log.debug("Deleting Ident with name '%s'", name->c_str());
}

Ident* Ident::clone() const {
    return new Ident(*this);
}

const string* Ident::getName() const {
    return name.get();
}

const TypePtr Ident::getType() const {
    return type;
}

void Ident::setType(const TypePtr t)
{
    s_assert(t);
    log.debug("Setting ident %s to type %s", name->c_str(), t->getId().c_str());
    type = t;
}

Value* Ident::compile(CodeGen& gen) const
{
    log.debug("Compiling Ident '%s'", name->c_str());

    IRBuilder<>* b = gen.getBuilder();

    const string name_string(*name);

    const Value* ptr_to_load = gen.getValue(name_string); // needs to come from somewhere
    s_assert_notnull(ptr_to_load);

    LoadInst* load_inst = b->CreateLoad((Value*)ptr_to_load, false, name_string);

    return load_inst;
}

void Snowy::Ident::to_sstream(std::ostringstream& s) const
{
    s_assert_cmpint(name->length(), >, 0);
    s_assert_cmpint(name->length(), <, 100);

    s << "Ident[" << *name;
    if (type) {
        s << " type=" << type->getId();
    }
    s << "]";
}

}
