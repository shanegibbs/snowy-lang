#include <glib.h>
#include <sstream>
#include <string.h>

#include <Node.h>

#include "Driver.h"

namespace Snowy
{

const Log Driver::log = Log("Driver");

Driver::Driver()
{
    program_parser = new ProgramParser(this);
}

int Driver::mylex(ProgramParser::semantic_type *val)
{
    // exec yylex
    int i = lexer->yylex();

    log.debug("Called mylex - %d, %s", i, lexer->YYText());

    // need to copy string as it will get nurfed when the
    // parser does a look ahead
    val->string = (const char*)malloc(strlen(lexer->YYText() + 1));
    strcpy((char*)val->string, lexer->YYText());

    return i;
}

Node* Driver::exec()
{
    g_assert_nonnull(lexer);
    program_parser->parse();
    return root;
}

void Driver::error(const char* err)
{
    log.fatal("Snowy Parse Error: %s", err);
    root = NULL;
}

}
