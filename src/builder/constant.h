#ifndef INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2
#define INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2

#include "builder/types.h"

Constant *constant_new(void);
void constant_delete(Constant *);
void constant_print(Constant *);

Constant *builder_new_integer(Builder *, const char *);

#endif /* INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2 */
