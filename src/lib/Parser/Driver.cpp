#include <glib.h>
#include <sstream>
#include <FlexLexer.h>

#include <Node.h>

#include "Driver.h"

extern const char *mystr;

Snowy::Driver::Driver()
{
    // puts("new Driver");
    lexer = new yyFlexLexer;
    program_parser = new Snowy::ProgramParser(this);
}

int Snowy::Driver::mylex(ProgramParser::semantic_type *val)
{
    int i = lexer->yylex();
    // printf("Called mylex - %d, %s\n", i, lexer->YYText());
    val->string = lexer->YYText();
    return i;
}

Snowy::Node* Snowy::Driver::parse()
{
    return exec();
}

Snowy::Node* Snowy::Driver::parse(const char *string)
{
    std::stringstream ss;
    ss << string;
    lexer = new yyFlexLexer((std::istream*)&ss);
    return exec();
}

Snowy::Node* Snowy::Driver::parse(FILE *steam)
{
    printf("No impl\n");
    return NULL;
}

Snowy::Node* Snowy::Driver::exec()
{
    program_parser->parse();
    return root;
}

void Snowy::Driver::error(const char* err)
{
    printf("Snowy Parse Error: %s\n", err);
    root = NULL;
}
