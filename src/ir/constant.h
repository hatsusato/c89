#ifndef INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2
#define INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2

#include "utility/types.h"

Constant *constant_new(Module *, const char *, Type *);
void constant_delete(Constant *);
Type *constant_type(Constant *);
void constant_print(Constant *);

void builder_new_integer(Builder *, const char *);

#endif /* INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2 */
