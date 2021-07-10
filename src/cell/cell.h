#ifndef INCLUDE_GUARD_04E54D27_C0FE_495E_B0BD_7A663768CFF5
#define INCLUDE_GUARD_04E54D27_C0FE_495E_B0BD_7A663768CFF5

#include "util/type.h"

struct cell;
struct pool;

const struct cell *cell_nil(void);
const struct cell *cell_new_cons(struct pool *, const struct cell *,
                                 const struct cell *);
const struct cell *cell_new_symbol(struct pool *, const char *);
bool_t cell_is_nil(const struct cell *);
bool_t cell_is_cons(const struct cell *);
bool_t cell_is_symbol(const struct cell *);

#endif /* INCLUDE_GUARD_04E54D27_C0FE_495E_B0BD_7A663768CFF5 */
