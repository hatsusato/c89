#ifndef INCLUDE_GUARD_76DFC357_C3ED_4072_88BC_20349BB0834A
#define INCLUDE_GUARD_76DFC357_C3ED_4072_88BC_20349BB0834A

#include "util/type.h"

struct pool_any;

struct pool_any *pool_any_new(void);
void pool_any_delete(struct pool_any *);
void *pool_any_alloc(struct pool_any *, size_t);

#endif /* INCLUDE_GUARD_76DFC357_C3ED_4072_88BC_20349BB0834A */
