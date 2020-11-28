#ifndef INCLUDE_GUARD_3328774C_9C13_4B31_8826_622558B21C09
#define INCLUDE_GUARD_3328774C_9C13_4B31_8826_622558B21C09

#include "ir/pool_type.h"
#include "ir/value_type.h"

Pool *pool_new(void);
void pool_delete(Pool *);
Value *pool_alloc(Pool *, ValueKind);

#endif /* INCLUDE_GUARD_3328774C_9C13_4B31_8826_622558B21C09 */
