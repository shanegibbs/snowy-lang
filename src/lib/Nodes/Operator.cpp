#include "Operator.h"

#include <SnowyAssert.h>

namespace Snowy
{

const Log Operator::log = Log("Operator");

Operator::Operator(const char* op_str)
{
    init(op_str);
}

Operator::Operator(const string* op_str)
{
    init(*op_str);
    delete op_str;
}

Operator::~Operator()
{
    log.debug("Deleting Operator");
}

void Operator::init(const string& op_str)
{
    if (op_str == "+") {
        op = OP_PLUS;
    } else if (op_str == "-") {
        op = OP_MINUS;
    } else if (op_str == "*") {
        op = OP_MULTIPLY;
    } else if (op_str == "/") {
        op = OP_DIVIDE;
    } else {
        log.fatal("Unknown operator found: '%s'", op_str.c_str());
    }
}

void Snowy::Operator::to_sstream(std::ostringstream& s) const
{
    switch(op) {
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
