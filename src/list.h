#ifndef INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F
#define INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F

#include "struct.h"

List *list_new(int, void *);
void list_delete(List *, void (*)(List *));
int list_tag(List *);
void *list_data(List *);
List *list_next(List *);
List *list_last(List *);
void list_insert(List *, List *);

#endif /* INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F */
