#ifndef INCLUDE_GUARD_B4E15810_2F41_4F54_A991_687F0FFE8ED4
#define INCLUDE_GUARD_B4E15810_2F41_4F54_A991_687F0FFE8ED4

#include "pool_type.h"
#include "types.h"

Pool *pool_new(Destructor);
void pool_delete(Pool *);
const char *pool_construct(const char *, Size);
void pool_destruct(ElemType);
const char *pool_insert(Pool *, const char *, Size);
Bool pool_contains(Pool *, const char *);

#endif /* INCLUDE_GUARD_B4E15810_2F41_4F54_A991_687F0FFE8ED4 */
