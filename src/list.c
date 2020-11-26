#include "list.h"

#include "node.h"
#include "utility.h"

struct struct_List {
  Node *first, *last;
  Destructor dtor;
};

static void list_destructor_default(ElemType e) {
  UTILITY_UNUSED(e);
}

List *list_new(Destructor dtor) {
  List *list = UTILITY_MALLOC(List);
  list->first = list->last = NULL;
  list->dtor = dtor ? dtor : list_destructor_default;
  return list;
}
void list_delete(List *list) {
  assert(list);
  while (list->first) {
    list_remove(list);
  }
  UTILITY_FREE(list);
}
void list_insert(List *list, ElemType elem) {
  assert(list);
  list->first = node_new(elem, list->first);
  if (!list->last) {
    list->last = list->first;
  }
}
void list_remove(List *list) {
  assert(list && list->first);
  list->first = node_delete(list->first, list->dtor);
  if (!list->first) {
    list->last = NULL;
  }
}
void list_append(List *lhs, List *rhs) {
  assert(lhs && rhs);
  assert(lhs->dtor == rhs->dtor);
  if (rhs->last) {
    if (lhs->last) {
      node_insert(lhs->last, rhs->first);
    } else {
      lhs->first = rhs->first;
    }
    lhs->last = rhs->last;
  }
  rhs->first = rhs->last = NULL;
}
void list_map(List *list, void *data, ListMap map) {
  Node *node = NULL;
  assert(list);
  for (node = list->first; node; node = node_next(node)) {
    map(node_get(node), data);
  }
}
ElemType list_at(List *list, Index index) {
  Node *node = NULL;
  Index i = 0;
  assert(list);
  for (node = list->first; node; node = node_next(node), ++i) {
    if (i == index) {
      return node_get(node);
    }
  }
  return NULL;
}
