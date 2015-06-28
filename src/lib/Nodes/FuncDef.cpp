#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Argument.h>

#include <CodeGen.h>
#include <SnowyAssert.h>
#include <Log.h>

#include "FuncDef.h"
#include "Type.h"
#include "ArgsDecl.h"
#include "Ident.h"

using namespace llvm;

namespace Snowy
{

const Log FuncDef::log = Log("FuncDef");

FuncDef::FuncDef(const Ident* i, const ArgsDecl* a, const Node* b = NULL) : ident(i), args(a), block(b == NULL ? NULL : b->getFirst())
{
    s_assert_notnull(i);
    s_assert_notnull(a);

    log.debug("Creating DeclarerFunc node %s", ident->getName()->c_str());
}

FuncDef::~FuncDef()
{
    delete ident;
    delete args;
    if (block != NULL) {
        delete block;
    }
}

FuncDef* FuncDef::clone() const
{
    return new FuncDef(*this);
}

const string& FuncDef::getName() const {
    return *ident->getName();
}

const TypePtr FuncDef::getType() const
{
    return ident->getType();
}

void FuncDef::to_sstream(std::ostringstream& s) const
{
    s << "FuncDef=[ident=[";
    ident->to_sstream(s);
    s << "] args=[";
    args->to_sstream(s);
    s << "] block=[";
    if (block == NULL) {
        s << "NULL";
    } else {
        s << endl;
        const Node* current = block;
        while (current != NULL) {
            s << " ";
            current->to_sstream(s);
            s << endl;
            current = current->getNext();
        }
    }
    s << "]]";
}

Value* FuncDef::compile(CodeGen& gen) const
{
    log.debug("Compiling function '%s'", ident->getName()->c_str());
    LLVMContext* context = &gen.getBuilder()->getContext();
    IRBuilder<>& b = *gen.getBuilder();

    // TODO map types
    std::vector<llvm::Type*> fn_args;
    for (unsigned int i = 0; i < args->size(); i++) {
        llvm::Type* argType = llvm::Type::getInt32Ty(*context);
        fn_args.push_back(argType);
    }

    FunctionType *ft = FunctionType::get(llvm::Type::getInt32Ty(*context), fn_args, false);

    Function* fn = Function::Create(ft, Function::ExternalLinkage, *ident->getName(), gen.getModule());
    gen.registerFunction(fn);

    BasicBlock *bb = BasicBlock::Create(getGlobalContext(), *ident->getName(), fn);
    BasicBlock* last_block = gen.getBuilder()->GetInsertBlock();
    gen.getBuilder()->SetInsertPoint(bb);

    // store each arg in memory so that it can be retreived
    // by the Ident node
    unsigned int i = 0;
    for (Function::arg_iterator it = fn->arg_begin(); i != args->size(); ++it, ++i) {
        it->setName(*args->getIdent(i).getName());

        log.debug("Saving arg '%s' into memory", args->getIdent(i).getName()->c_str());
        llvm::Type* mem_type = llvm::Type::getInt32Ty(*context);
        ConstantInt* mem_count = b.getInt32(1);
        AllocaInst* mem = b.CreateAlloca(mem_type, mem_count, "arg_ptr");

        b.CreateStore(it, mem); // just returns a void Value
        gen.registerValue(*args->getIdent(i).getName(), mem);
    }

    // generate function termintaor
    Value* terminator = NULL;
    if (block != NULL) {
        const Node *current = block;
        while (current != NULL) {
            log.debug("Compiling node in block");
            terminator = current->compile(gen);
            current = current->getNext();
            if (current == NULL) {
                log.debug("Next node in block is NULL");
            }
        }
    } else {
        terminator = ConstantInt::get(*context, APInt(32, 0, false));
    }
    gen.getBuilder()->CreateRet(terminator);

    gen.getBuilder()->SetInsertPoint(last_block);

    return fn;
}

}
