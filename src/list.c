#include "list.h"

#include <stdlib.h>

#include "utility.h"

struct struct_Node {
  int tag;
  void *data;
  Node *next;
};
struct struct_List {
  int tag;
  void *data;
  List *next;
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
  list->tag = tag;
  list->data = data;
  list->next = nil;
  return list;
}
void list_delete(List *list) {
  List *next = nil;
  while (list) {
    next = list->next;
    free(list);
    list = next;
  }
}
int list_get_tag(List *list) {
  assert(list);
  return list->tag;
}
void *list_get_data(List *list) {
  assert(list);
  return list->data;
}
