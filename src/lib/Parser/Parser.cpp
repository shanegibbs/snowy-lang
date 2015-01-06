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

Node* Parser::parse(istream& ins)
{
    log.info("Parsing file");
    driver->setLexer(new yyFlexLexer(&ins));
    return driver->exec();
}

}
