#ifndef INCLUDE_GUARD_04E54D27_C0FE_495E_B0BD_7A663768CFF5
#define INCLUDE_GUARD_04E54D27_C0FE_495E_B0BD_7A663768CFF5

struct cell;
struct pool;

const struct cell *cell_nil(void);
const struct cell *cell_new_cons(struct pool *, const struct cell *,
                                 const struct cell *);

#endif /* INCLUDE_GUARD_04E54D27_C0FE_495E_B0BD_7A663768CFF5 */
