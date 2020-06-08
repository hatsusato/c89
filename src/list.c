#include "list.h"

#include <stdlib.h>

#include "utility.h"

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
void list_delete(List *list) {
  assert(list);
  node_delete(list->node.next);
  free(list);
}
Node *list_begin(List *list) {
  assert(list);
  return &list->node;
}
Node *list_end(List *list) {
  Node *node = nil;
  assert(list);
  node = list_begin(list);
  while (node->next) {
    node = node->next;
  }
  return node;
}
int list_get_tag(Node *node) {
  assert(node && node->next);
  return node->next->tag;
}
void *list_get_data(Node *node) {
  assert(node && node->next);
  return node->next->data;
}
