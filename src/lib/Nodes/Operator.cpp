#include "Operator.h"

#include <SnowyAssert.h>

namespace Snowy {

const Log Operator::log = Log("Operator");

Operator::Operator(const shared_ptr<const string> op_str) {
  if (strcmp(op_str->c_str(), "+") == 0) {
    op = OP_PLUS;
  } else if (strcmp(op_str->c_str(), "-") == 0) {
    op = OP_MINUS;
  } else if (strcmp(op_str->c_str(), "*") == 0) {
    op = OP_MULTIPLY;
  } else if (strcmp(op_str->c_str(), "/") == 0) {
    op = OP_DIVIDE;
  } else {
    log.fatal("Unknown operator found: '%s'", op_str->c_str());
  }
}

Operator::~Operator() { log.debug("Deleting Operator"); }

void Snowy::Operator::to_sstream(std::ostringstream &s) const {
  switch (op) {
    case OP_PLUS:
      s << "+";
      break;

    case OP_MINUS:
      s << "-";
      break;

    case OP_MULTIPLY:
      s << "*";
      break;

    case OP_DIVIDE:
      s << "/";
      break;
  }
}
}
