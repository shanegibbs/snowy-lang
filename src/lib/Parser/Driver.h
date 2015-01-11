#ifndef SNOWY_DRIVER_HPP
#define SNOWY_DRIVER_HPP

#include <string>
#include <FlexLexer.h>

#include <Log.h>
#include <ProgramParser.h>

class FlexLexer;

namespace Snowy
{

class Log;

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

    const char* getTokenString(int) const;

private:
    static const Log log;
    Node* root;
    FlexLexer* lexer;
    ProgramParser *program_parser;
    int line_number;
    int column_number;
};

}
#endif
