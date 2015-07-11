#include <stdlib.h>
#include <string>
#include <cstring>

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>

#include <Log.h>
#include <SnowyAssert.h>
#include <CodeGen.h>

#include "Node.h"

static int next_node_index = 1;

using namespace llvm;
using namespace std;

namespace Snowy {

const Log Node::log = Log("Node");

Node::Node() : node_id(next_node_index++) {
  log.trace("Created node with ID %d\n", node_id);
  first = this;
  next = nullptr;
}

Node::~Node() {
  log.trace("Deleting node %d", node_id);

  if (next != nullptr) {
    // log.debug("Deleting next node");
    delete next;
  }
}

Node *Node::getFirst() const {
  s_assert_notnull(first);
  return first;
}

void Node::setNext(Node *n) {
  // printf("Attaching nodes %d -> %d\n", id, n->id);
  next = n;
  n->first = first;
}

const char *Node::to_string() const {
  ostringstream oss;
  to_sstream(oss);
  oss << endl;

  string oss_str = oss.str();
  const char *oss_out = oss_str.c_str();

  char *cstr = new char[strlen(oss_out) + 1];
  strcpy(cstr, oss_out);
  s_assert_cmpstr(cstr, oss.str().c_str());

  return cstr;
}

const string Node::to_program_string() const {
  ostringstream oss;

  const Node *current = this;

  while (current != NULL) {
    current->to_sstream(oss);
    oss << endl;
    current = current->next;
  }

  return oss.str();
}

Value *Node::compileBlock(CodeGen &gen, BasicBlock *returnTo) const {
  log.debug("Compiling block. Will return to %s", returnTo->getName());

  Value *value = NULL;
  const Node *n = this;
  while (n != NULL) {
    value = n->compile(gen);
    n = n->getNext();

    if (n == nullptr) {
      log.debug("Found end of block. Returning to %s", returnTo->getName());
      BranchInst::Create(returnTo, gen.getBuilder()->GetInsertBlock());
      gen.getBuilder()->SetInsertPoint(returnTo);
    }
  }

  return value;
}
}
