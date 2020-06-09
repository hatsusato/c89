#include "list.h"

#include <stdlib.h>

#include "utility.h"

struct struct_List {
  int tag;
  void *data;
  List *next;
};

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
int list_tag(List *list) {
  assert(list);
  return list->tag;
}
void *list_data(List *list) {
  assert(list);
  return list->data;
}
List *list_next(List *list) {
  assert(list);
  return list->next;
}
List *list_last(List *list) {
  assert(list);
  while (list->next) {
    list = list->next;
  }
  return list;
}
