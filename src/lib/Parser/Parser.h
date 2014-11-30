#ifndef SNOWY_PARSER_HPP
#define SNOWY_PARSER_HPP

#include <string>

namespace Snowy
{

class Log;
class Driver;
class Node;

class Parser
{
public:
    Parser();

    Node* parse();
    Node* parse(FILE *);
    Node* parse(const char *);

private:
    static const Log log;
    Driver* driver;
};

}
#endif
