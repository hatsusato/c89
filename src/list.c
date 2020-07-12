#include "list.h"

#include "node.h"
#include "utility.h"

struct struct_List {
  Node *first, *last;
  Destructor dtor;
};

static void list_destructor_default(ElemType e) {
  (void)e;
}

List *list_new(Destructor dtor) {
  List *list = UTILITY_MALLOC(List);
  list->first = list->last = NULL;
  list->dtor = dtor ? dtor : list_destructor_default;
  return list;
}
void list_delete(List *list) {
  Node *node = list->first;
  while (node) {
    node = node_delete(node, list->dtor);
  }
  UTILITY_FREE(list);
}
void list_insert(List *list, ElemType elem) {
  list->first = node_new(elem, list->first);
  if (!list->last) {
    list->last = list->first;
  }
}
void list_append(List *lhs, List *rhs) {
  assert(lhs->dtor == rhs->dtor);
  if (rhs->last) {
    if (lhs->last) {
      node_insert(lhs->last, rhs->first);
    } else {
      lhs->first = rhs->first;
    }
    lhs->last = rhs->first = NULL;
    UTILITY_SWAP(Node *, lhs->last, rhs->last);
  }
}
