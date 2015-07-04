#include <llvm/IR/Constants.h>

#include <Log.h>
#include <SnowyAssert.h>
#include <CodeGen.h>

#include "BoolLiteral.h"

using namespace llvm;

namespace Snowy {

const Log BoolLiteral::log = Log("BoolLiteral");

static bool parseBool(const shared_ptr<const string> str) {
  return strcasecmp(str->c_str(), "true") == 0;
}

BoolLiteral::BoolLiteral(const shared_ptr<const string> str)
    : val(parseBool(str)) {
  s_assert_notnull(str.get());
  log.debug("Creating BoolLiteral %s", val ? "true" : "false");
}

void BoolLiteral::to_sstream(ostringstream &s) const {
  s << "BoolLiteral=[" << (val ? "true" : "false") << "]";
}

llvm::Value *BoolLiteral::compile(CodeGen &gen) const {
  log.debug("Compiling BoolLiteral %s", val ? "true" : "false");
  LLVMContext *context = &gen.getBuilder()->getContext();
  if (val) {
    return ConstantInt::get(*context, APInt(1, 1, false));
  } else {
    return ConstantInt::get(*context, APInt(1, 0, false));
  }
}
}
