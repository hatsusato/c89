#ifndef INCLUDE_GUARD_BFACDD17_F309_4216_B735_6340D39BC17A
#define INCLUDE_GUARD_BFACDD17_F309_4216_B735_6340D39BC17A

#include "builder/type.h"

Global *global_new(void);
void global_delete(Global *);
void global_set_init(Global *, Constant *);
void global_print(Global *);
void global_pretty(Global *);

Global *builder_new_global(Builder *, const char *);

#endif /* INCLUDE_GUARD_BFACDD17_F309_4216_B735_6340D39BC17A */
