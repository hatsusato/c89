#ifndef INCLUDE_GUARD_88506381_726D_4317_A13B_6980767D83BC
#define INCLUDE_GUARD_88506381_726D_4317_A13B_6980767D83BC

#include "builder/types.h"
#include "compare/types.h"
#include "spec.h"

int type_cmp(ElemType, ElemType, CompareExtra);
Type *type_new(void);
Type *type_new_spec(TypeSpec *);
void type_delete(ElemType);

Bool type_is_void(Type *);
void type_print(Type *);
void type_print_elem(Type *);

#endif /* INCLUDE_GUARD_88506381_726D_4317_A13B_6980767D83BC */
