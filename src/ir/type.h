#ifndef INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1
#define INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1

#include "type/print.h"
#include "utility/types.h"
#include "vector/typedef.h"

int type_cmp_for_vector(const VectorCmpElem *, const VectorCmpElem *);
Compare *type_compare_new(void);
Set *type_set_new(Compare *);
void type_set_delete(Set *);

Bool type_equals(Type *, Type *);
Bool type_is_void(Type *);
int type_sizeof(Type *);

#endif /* INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1 */
