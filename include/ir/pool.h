#ifndef INCLUDE_GUARD_3328774C_9C13_4B31_8826_622558B21C09
#define INCLUDE_GUARD_3328774C_9C13_4B31_8826_622558B21C09

#include "ir/function_type.h"
#include "ir/pool_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"

Pool *pool_new(void);
void pool_delete(Pool *);
void pool_insert(Pool *, Value *);
void pool_insert_function(Pool *, Function *);

#endif /* INCLUDE_GUARD_3328774C_9C13_4B31_8826_622558B21C09 */
