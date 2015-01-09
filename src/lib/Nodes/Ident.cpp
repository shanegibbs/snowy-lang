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

using namespace llvm;

namespace Snowy
{

const Log Ident::log = Log("Ident");

void Ident::init()
{
    s_assert_notnull(name);
    s_assert_cmpint(name->length(), >, 0);
    s_assert_cmpint(name->length(), <, 100);
    log.debug("Creating Ident with name '%s'", name->c_str());
}

Ident::Ident(const char* n) : name(new string(n))
{
    s_assert_notnull(n);
    init();
}

Ident::Ident(const string* n) : name(n)
{
    init();
}

Ident::~Ident()
{
    delete name;
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

    s << "Ident[" << *name << "]";
}

}
