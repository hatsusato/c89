#ifndef INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1
#define INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1

#include "type/print.h"
#include "utility/types.h"
#include "vector/typedef.h"

typedef Set TypePool;

Bool type_equals(Type *, Type *);
Bool type_is_void(Type *);
int type_sizeof(Type *);

TypePool *type_pool_new(void);
void type_pool_delete(TypePool *);
void type_pool_insert(TypePool *, Type *);
Type *type_pool_find(TypePool *, Type *);

#endif /* INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1 */
