#include <stdio.h>
#include <stdlib.h>
#include <cstring>
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

Ident::Ident(const char* n)
{
    log.debug("Creating Ident with name '%s'", n);

    s_assert_notnull(n);
    s_assert_cmpint(strlen(n), >, 0);
    s_assert_cmpint(strlen(n), <, 100);

    char* new_name = (char*)malloc(strlen(n) + 1);
    strcpy(new_name, n);
    name = new_name;
    s_assert_cmpstr(n, name);
}

Value* Ident::compile(CodeGen& gen) const
{
    log.debug("Compiling Ident '%s'", name);

    IRBuilder<>* b = gen.getBuilder();

    const string name_string(name);

    const Value* ptr_to_load = gen.getValue(name_string); // needs to come from somewhere
    s_assert_notnull(ptr_to_load);

    LoadInst* load_inst = b->CreateLoad((Value*)ptr_to_load, false, name_string);

    return load_inst;
}

void Snowy::Ident::to_sstream(std::ostringstream& s) const
{
    s_assert_notnull(name);
    s_assert_cmpint(strlen(name), >, 0);
    s_assert_cmpint(strlen(name), <, 100);

    s << "Ident[" << name << "]";
}

}
