#ifndef INCLUDE_GUARD_B55311C7_57F5_41B3_92DD_0759ECC346E7
#define INCLUDE_GUARD_B55311C7_57F5_41B3_92DD_0759ECC346E7

#include "ir/function_type.h"
#include "ir/pool.h"

Function *function_new(Pool *);
void function_delete(Function *);
void function_insert_allocs(Function *);

#endif /* INCLUDE_GUARD_B55311C7_57F5_41B3_92DD_0759ECC346E7 */
