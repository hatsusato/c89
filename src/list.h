#ifndef INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F
#define INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F

#include "typedef.h"

List *list_new(ElemType, Destructor);
void list_delete(List *);
ElemType list_get(List *);
List *list_next(List *);
List *list_last(List *);
void list_insert(List *, List *);

#endif /* INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F */
