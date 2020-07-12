#include "list.h"

#include "utility.h"

struct struct_List {
  ElemType elem;
  Destructor dtor;
  List *next;
};

static void list_destructor_default(ElemType e) {
  (void)e;
}

List *list_new(ElemType elem, Destructor dtor) {
  List *list = UTILITY_MALLOC(List);
  list->elem = elem;
  list->dtor = dtor ? dtor : list_destructor_default;
  list->next = NULL;
  return list;
}
void list_delete(List *list) {
  List *next = NULL;
  while (list) {
    next = list->next;
    list->dtor(list->elem);
    UTILITY_FREE(list);
    list = next;
  }
}
