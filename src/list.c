#include "list.h"

#include <stdlib.h>

#include "utility.h"

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
void node_delete(Node *node) {
  Node *next = nil;
  while (node) {
    next = node->next;
    free(node);
    node = next;
  }
}

List *list_new(int tag, void *data) {
  List *list = malloc(sizeof(List));
  list->node.tag = 0;
  list->node.data = nil;
  list->node.next = node_new(tag, data, nil);
  return list;
}
