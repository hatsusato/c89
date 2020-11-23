#ifndef INCLUDE_GUARD_EE46CC10_6993_423D_BD00_80BDCB6B3815
#define INCLUDE_GUARD_EE46CC10_6993_423D_BD00_80BDCB6B3815

#include "types.h"
#include "vector/pool_type.h"

Pool *pool_new(void);
void pool_delete(Pool *);
const void *pool_insert(Pool *, const void *, Size);

#endif /* INCLUDE_GUARD_EE46CC10_6993_423D_BD00_80BDCB6B3815 */
