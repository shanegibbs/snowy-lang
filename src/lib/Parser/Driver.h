#ifndef SNOWY_DRIVER_HPP
#define SNOWY_DRIVER_HPP

#include <string>
#include <FlexLexer.h>

#include <ProgramParser.h>

class FlexLexer;

namespace Snowy
{

class Driver
{
public:
    Driver();
    ~Driver();

    int mylex(ProgramParser::semantic_type *);

    void error(const char*);

    Node* exec();

    void setLexer(FlexLexer* l)
    {
        lexer = l;
    }

    void setRoot(Node *r)
    {
        root = r;
    }

private:
    Node* root;
    FlexLexer* lexer;
    ProgramParser *program_parser;
};

}
#endif
