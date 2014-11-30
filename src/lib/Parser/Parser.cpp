#include <glib.h>
#include <sstream>
#include <FlexLexer.h>

#include <Node.h>

#include "Driver.h"
#include "Parser.h"

namespace Snowy
{

const Log Parser::log = Log("Parser");

Parser::Parser()
{
    driver = new Driver;
}

Node* Parser::parse()
{
    driver->setLexer(new yyFlexLexer);
    return driver->exec();
}

Node* Parser::parse(const char *string)
{
    log.info("Parsing: %s", string);
    std::stringstream ss;
    ss << string;
    driver->setLexer(new yyFlexLexer((std::istream*)&ss));
    return driver->exec();
}

Node* Parser::parse(FILE *steam)
{
    log.warn("No impl");
    return NULL;
}

}
