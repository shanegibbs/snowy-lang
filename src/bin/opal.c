#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib.h>

#include "nodes.h"
#include "opal.h"

void exec_lex();
int yyparse();
int yydebug;

void print_node(Node *node)
{
    while (node != NULL) {
        printf("%s\n", get_node_desc(node));
        node = node->node_next;
    }
}

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

    printf("\nPrinting node graph:\n");
    print_node(root);

}
