#ifndef INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2
#define INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2

#include "ir/constant_type.h"
#include "ir/stack_type.h"

Constant *constant_new(void);
Constant *constant_integer(const char *);
void constant_delete(Constant *);
void constant_print(Constant *);

Constant *stack_new_integer(Stack *, const char *);

#endif /* INCLUDE_GUARD_847C4618_BC3A_4B3B_AB91_0840BEF9BDE2 */
