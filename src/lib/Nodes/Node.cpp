#include <stdlib.h>
#include <cstring>
#include <glib.h>

#include <Log.h>
#include <Assert.h>

#include "Node.h"

static int next_node_index = 1;

using namespace llvm;
using namespace std;

namespace Snowy
{

const Log Node::log = Log("Node");

Node::Node()
{
    id = next_node_index++;
    // printf("Created node with ID %d\n", id);
    next = NULL;
}

void Node::setNext(Node *n)
{
    // printf("Attaching nodes %d -> %d\n", id, n->id);
    next = n;
}

const char* Node::to_string()
{
    ostringstream oss;
    to_sstream(&oss);
    oss << endl;

    const char* oss_out = oss.str().c_str();
    char* cstr = new char[strlen(oss_out) + 1];
    strcpy(cstr, oss_out);
    s_assert_cmpstr(cstr, oss.str().c_str());

    return cstr;
}

const char* Node::to_program_string()
{
    ostringstream oss;

    Node* current = this;

    while (current != NULL) {
        current->to_sstream(&oss);
        oss << endl;
        current = current->next;
    }

    const string str = oss.str();
    g_assert_cmpuint(str.length(), >, 0);

    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());
    return cstr;
}

}
