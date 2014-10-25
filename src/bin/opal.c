#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <glib.h>

#include "nodes.h"

// void exec_lex();
// int yyparse();
// int yydebug;

void print_node(Node *node)
{
    while (node != NULL) {
        printf("%s\n", get_node_desc(node));
        node = node->node_next;
    }
}

int main(int argc, char** argv)
{
    // opal_parse_string("1+2\n");
    opal_stdin_parse();

    if (root == NULL) {
        printf("root is NULL\n");
        return 3;
    }

    printf("\nPrinting node graph:\n");
    print_node(root);

}
