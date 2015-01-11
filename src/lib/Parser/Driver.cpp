#include <sstream>
#include <string.h>

#include <SnowyAssert.h>
#include <Node.h>

#include "Driver.h"

namespace Snowy
{

const Log Driver::log = Log("Driver");

Driver::Driver()
{
    program_parser = new ProgramParser(this);
    line_number = 1;
    column_number = 1;
}

Driver::~Driver()
{
    log.debug("Destroying Driver");
    delete program_parser;
}

int Driver::mylex(ProgramParser::semantic_type *val)
{
    // exec yylex
    int i = lexer->yylex();

    int new_line_number = lexer->lineno();
    int new_column_number = column_number + lexer->YYLeng();

    log.debug("Called mylex - %s(%d), %s. Line %d-%d, column %d-%d.", getTokenString(i), i, lexer->YYText(), line_number, new_line_number, column_number, new_column_number - 1);

    line_number = new_line_number;
    column_number = new_column_number;

    // if whitespace, ignore and get the next token
    if (i == ProgramParser::token::WHITE_SPACE) {
        return mylex(val);
    }

    // need to copy string as it will get nurfed when the
    // parser does a look ahead
    if (i == ProgramParser::token::ID
            || i == ProgramParser::token::INTEGER
            || i == ProgramParser::token::STRING_LIT
            || i == ProgramParser::token::OP) {
        val->str = new string(lexer->YYText());
    }

    if (i == ProgramParser::token::ENDL) {
        column_number = 1;
    }

    return i;
}

Node* Driver::exec()
{
    s_assert_notnull(lexer);
    program_parser->parse();
    return root;
}

void Driver::error(const char* err)
{
    log.fatal("Snowy Parse Error: %s", err);
    root = NULL;
}

const char* Driver::getTokenString(int t) const
{
    switch(t) {
    case ProgramParser::token::ID:
        return "ID";
    case ProgramParser::token::INTEGER:
        return "INTEGER";
    case ProgramParser::token::STRING_LIT:
        return "STRING_LIT";
    case ProgramParser::token::EQ_OP:
        return "EQ_OP";
    case ProgramParser::token::OP:
        return "OP";
    case ProgramParser::token::COMMA:
        return "COMMA";
    case ProgramParser::token::OPEN_BRACKET:
        return "OPEN_BRACKET";
    case ProgramParser::token::CLOSE_BRACKET:
        return "CLOSE_BRACKET";
    case ProgramParser::token::DO:
        return "DO";
    case ProgramParser::token::END:
        return "END";
    case ProgramParser::token::ENDL:
        return "ENDL";
    case ProgramParser::token::WHITE_SPACE:
        return "WHITE_SPACE";
    }
    return "UNKNOWN";
}

}
