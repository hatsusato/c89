#ifndef INCLUDE_GUARD_BFACDD17_F309_4216_B735_6340D39BC17A
#define INCLUDE_GUARD_BFACDD17_F309_4216_B735_6340D39BC17A

#include "builder/type.h"
#include "sexp/type.h"
#include "types.h"

Global *global_new(void);
void global_delete(Global *);
void global_set_init(Global *, Constant *);
Bool global_get_prior(Global *);
void global_set_prior(Global *);
void global_print(Global *);
void global_pretty(Global *);

Global *builder_new_global(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_BFACDD17_F309_4216_B735_6340D39BC17A */
