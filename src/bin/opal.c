#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "nodes.h"
#include "opal.h"

void exec_lex();
int yyparse();
int yydebug;

int main(int argc, char** argv)
{
    /*
    char buffer[4096];
    int len = read(STDIN_FILENO, buffer, 4096);
    printf("len=%d\n", len);
    buffer[len] = 0;
    printf("%s\n", buffer);
    */

    // yyin = stdin;
    // yylex();

    // yy_scan_buffer("a test string");
    // yylex();

    // exec_lex();

    // yydebug = 1;
    yyparse();

    // printf("OK\n");

    if (root == NULL) {
        printf("root is NULL\n");
    }


}
