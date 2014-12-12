#include "Operator.h"

namespace Snowy
{

Operator::Operator(const char* op_str)
{
    if (strcmp(op_str, "+") == 0) {
        op = OP_PLUS;
    } else if (strcmp(op_str, "-") == 0) {
        op = OP_MINUS;
    }
}

void Snowy::Operator::to_sstream(std::ostringstream* s) const
{
    switch(op) {
    case OP_PLUS:
        *s << "+";
        break;
    case OP_MINUS:
        *s << "-";
        break;
    }
}

}
