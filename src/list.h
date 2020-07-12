#ifndef INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F
#define INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F

#include "typedef.h"

List *list_new(Destructor);
void list_delete(List *);
void list_insert(List *, ElemType);
void list_append(List *, List *);

#endif /* INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F */
