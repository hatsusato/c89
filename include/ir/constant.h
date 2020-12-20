#ifndef INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2
#define INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2

#include "ir/constant_type.h"
#include "ir/value_type.h"

Constant *constant_integer(const char *);
void constant_delete(Constant *);
Value *constant_as_value(Constant *);
void constant_print(Constant *);

#endif /* INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2 */
