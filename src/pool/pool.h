#ifndef INCLUDE_GUARD_76DFC357_C3ED_4072_88BC_20349BB0834A
#define INCLUDE_GUARD_76DFC357_C3ED_4072_88BC_20349BB0834A

#include "util/type.h"

struct pool;

struct pool *pool_new(void);
void pool_delete(struct pool *);
void *pool_alloc(struct pool *, size_t);

#endif /* INCLUDE_GUARD_76DFC357_C3ED_4072_88BC_20349BB0834A */
