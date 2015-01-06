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

Parser::~Parser()
{
    delete driver;
}

Node* Parser::parse()
{
    driver->setLexer(new yyFlexLexer);
    return driver->exec();
}

Node* Parser::parse(istream& ins)
{
    log.info("Parsing file");

    FlexLexer* lexer = new yyFlexLexer(&ins);
    driver->setLexer(lexer);

    Node* node = driver->exec();
    driver->setLexer(NULL);
    delete lexer;

    return node;
}

}
