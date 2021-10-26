#ifndef INCLUDE_GUARD_04E54D27_C0FE_495E_B0BD_7A663768CFF5
#define INCLUDE_GUARD_04E54D27_C0FE_495E_B0BD_7A663768CFF5

#include "util/type.h"

struct cell;

const struct cell *cell_nil(void);
bool_t cell_is_nil(const struct cell *);
bool_t cell_is_cons(const struct cell *);
bool_t cell_is_symbol(const struct cell *);
bool_t cell_is_list(const struct cell *);
const struct cell *cell_car(const struct cell *);
const struct cell *cell_cdr(const struct cell *);
const char *cell_symbol(const struct cell *);
const char *cell_tag(const struct cell *);
void cell_set_car(const struct cell *, const struct cell *);
void cell_set_cdr(const struct cell *, const struct cell *);

#endif /* INCLUDE_GUARD_04E54D27_C0FE_495E_B0BD_7A663768CFF5 */
