#include "Node.h"

static int next_node_index = 1;

Snowy::Node::Node()
{
    id = next_node_index++;
    // printf("Created node with ID %d\n", id);
    next = NULL;
}

void Snowy::Node::setNext(Node *n)
{
    // printf("Attaching nodes %d -> %d\n", id, n->id);
    next = n;
}

void Snowy::Node::to_sstream(std::ostringstream* s)
{
    *s << "Node[id=" << id << "]";
}

const char* Snowy::Node::to_string()
{
    std::ostringstream oss;
    to_sstream(&oss);
    oss << std::endl;

    const char* oss_out = oss.str().c_str();
    char* cstr = new char[strlen(oss_out) + 1];
    std::strcpy(cstr, oss_out);
    return cstr;
}

const char* Snowy::Node::to_program_string()
{
    std::ostringstream oss;

    Node* current = this;

    while (current != NULL) {
        current->to_sstream(&oss);
        oss << std::endl;

        current = current->next;
    }

    const char* oss_out = oss.str().c_str();
    char* cstr = new char[strlen(oss_out) + 1];
    std::strcpy(cstr, oss_out);
    return cstr;
}
