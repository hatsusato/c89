#include "node.h"

#include "utility.h"

struct struct_Node {
  ElemType elem;
  Node *next;
};

Node *node_new(ElemType elem, Node *next) {
  Node *node = UTILITY_MALLOC(Node);
  node->elem = elem;
  node->next = next;
  return node;
}
Node *node_delete(Node *node, Destructor dtor) {
  Node *next = node->next;
  dtor(node->elem);
  UTILITY_FREE(node);
  return next;
}
