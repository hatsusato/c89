#ifndef INCLUDE_GUARD_EE46CC10_6993_423D_BD00_80BDCB6B3815
#define INCLUDE_GUARD_EE46CC10_6993_423D_BD00_80BDCB6B3815

#include "compare_type.h"
#include "types.h"
#include "vector/pool_type.h"
#include "vector/vector_type.h"

Pool *pool_new(Vector *, Compare *);
void pool_delete(Pool *);
void pool_insert(Pool *, ElemType);
const ElemType *pool_find(Pool *, ElemType);

#endif /* INCLUDE_GUARD_EE46CC10_6993_423D_BD00_80BDCB6B3815 */
