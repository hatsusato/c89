#ifndef INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1
#define INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1

#include "builder/types.h"

Type *type_new(void);
void type_delete(Type *);

TypePool *type_pool_new(void);
void type_pool_delete(TypePool *);
Type *type_pool_integer(TypePool *, int);

#endif /* INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1 */
