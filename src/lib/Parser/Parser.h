#ifndef SNOWY_PARSER_HPP
#define SNOWY_PARSER_HPP

#include <string>

#include <Node.h>

namespace Snowy
{

class Driver;

class Parser
{
public:
    Parser();

    Node* parse();
    Node* parse(FILE *);
    Node* parse(const char *);

private:
    Driver* driver;
};

}
#endif
