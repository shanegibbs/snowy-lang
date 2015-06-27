#include <stdlib.h>
#include <string>
#include <cstring>

#include <Log.h>
#include <SnowyAssert.h>

#include "Node.h"

static int next_node_index = 1;

using namespace llvm;
using namespace std;

namespace Snowy
{

const Log Node::log = Log("Node");

Node::Node() : node_id(next_node_index++)
{
    // printf("Created node with ID %d\n", node_id);
    first = this;
    next = nullptr;
}

Node::~Node()
{
    // log.debug("Deleting node %d", node_id);
    if (next != nullptr) {
        // log.debug("Deleting next node");
        delete next;
    }
}

Node* Node::getFirst() const
{
    s_assert_notnull(first);
    return first;
}

void Node::setNext(Node *n)
{
    // printf("Attaching nodes %d -> %d\n", id, n->id);
    next = n;
    n->first = first;
}

const char* Node::to_string() const
{
    ostringstream oss;
    to_sstream(oss);
    oss << endl;

    string oss_str = oss.str();
    const char* oss_out = oss_str.c_str();

    char* cstr = new char[strlen(oss_out) + 1];
    strcpy(cstr, oss_out);
    s_assert_cmpstr(cstr, oss.str().c_str());

    return cstr;
}

const string Node::to_program_string() const
{
    ostringstream oss;

    const Node* current = this;

    while (current != NULL) {
        current->to_sstream(oss);
        oss << endl;
        current = current->next;
    }

    return oss.str();
}

}
