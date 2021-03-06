#ifndef INCLUDE_GUARD_BFACDD17_F309_4216_B735_6340D39BC17A
#define INCLUDE_GUARD_BFACDD17_F309_4216_B735_6340D39BC17A

#include "utility/types.h"

Global *global_new(Module *, const char *, Type *);
void global_delete(Global *);
Type *global_type(Global *);
void global_set_init(Global *, Constant *);
Bool global_is_prior(Global *);
void global_set_prior(Global *);
void global_print(Global *, Printer *);
void global_print_type(Global *, Printer *);
void global_pretty(Global *, Printer *);

#endif /* INCLUDE_GUARD_BFACDD17_F309_4216_B735_6340D39BC17A */
