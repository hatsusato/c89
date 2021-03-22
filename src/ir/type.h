#ifndef INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1
#define INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1

#include "type/print.h"
#include "utility/types.h"
#include "vector/typedef.h"

void type_delete(VectorElem);
int type_cmp(const VectorCmpElem *, const VectorCmpElem *);
Bool type_equals(Type *, Type *);
Bool type_is_void(Type *);
int type_sizeof(Type *);

#endif /* INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1 */
