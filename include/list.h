#ifndef INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F
#define INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F

#include "list_type.h"
#include "types.h"

typedef void (*ListMap)(ElemType, void *);

List *list_new(Destructor);
void list_delete(List *);
void list_insert(List *, ElemType);
void list_remove(List *);
void list_append(List *, List *);
void list_map(List *, void *, ListMap);
ElemType list_at(List *, Index);

#endif /* INCLUDE_GUARD_A22A8A22_8237_41B8_A841_CCF37171764F */
