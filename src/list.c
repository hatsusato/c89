#include "list.h"

#include <stdlib.h>

struct struct_Node;
typedef struct struct_Node Node;
struct struct_Node {
  int tag;
  void *data;
  Node *next;
};
struct struct_List {
  Node node;
};

Node *node_new(int tag, void *data, Node *next) {
  Node *node = malloc(sizeof(Node));
  node->tag = tag;
  node->data = data;
  node->next = next;
  return node;
}
