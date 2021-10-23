#ifndef INCLUDE_GUARD_2279A9B0_1CB3_48E5_BEA4_AFE820D7CFD1
#define INCLUDE_GUARD_2279A9B0_1CB3_48E5_BEA4_AFE820D7CFD1

#include <stdarg.h>

#include "util/type.h"

struct cell_factory;
struct pool_any;
struct set_symbol;

const struct cell *cell_factory_push(struct cell_factory *, const struct cell *,
                                     const struct cell *);
struct cell_factory *cell_factory_new(struct pool_any *, struct set_symbol *);
void cell_factory_delete(struct cell_factory *);
const struct cell *cell_factory_cons(struct cell_factory *, const struct cell *,
                                     const struct cell *);
const struct cell *cell_factory_symbol(struct cell_factory *, const char *);
const struct cell *cell_factory_list(struct cell_factory *, index_t, va_list);

#endif /* INCLUDE_GUARD_2279A9B0_1CB3_48E5_BEA4_AFE820D7CFD1 */
