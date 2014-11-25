#include <glib.h>
#include <sstream>

#include <Node.h>

#include "Driver.h"

namespace Snowy
{

Driver::Driver()
{
    program_parser = new ProgramParser(this);
}

int Driver::mylex(ProgramParser::semantic_type *val)
{
    // exec yylex
    int i = lexer->yylex();

    g_debug("Called mylex - %d, %s\n", i, lexer->YYText());

    // set return values
    val->string = lexer->YYText();
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
    printf("Snowy Parse Error: %s\n", err);
    root = NULL;
}

}
