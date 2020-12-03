#ifndef INCLUDE_GUARD_B55311C7_57F5_41B3_92DD_0759ECC346E7
#define INCLUDE_GUARD_B55311C7_57F5_41B3_92DD_0759ECC346E7

#include "ir/function_type.h"
#include "ir/pool.h"
#include "ir/value_type.h"

typedef enum {
  FUNCTION_FUNC,
  FUNCTION_ALLOCS,
  FUNCTION_CURRENT,
  FUNCTION_NEXT,
  FUNCTION_RET,
  FUNCTION_COUNT
} FunctionMember;

Function *function_new(Pool *);
void function_delete(Function *);
Value *function_get(Function *, FunctionMember);
void function_set(Function *, FunctionMember, Value *);

void function_insert_allocs(Function *);
void function_insert_to_allocs(Function *, Value *);
void function_insert_to_current(Function *, Value *);
void function_set_current(Function *, Value *);
Value *function_get_return(Function *);
void function_set_return(Function *, Value *);

Value *function_get_func(Function *);
void function_set_func(Function *, Value *);
Value *function_get_next(Function *);
void function_set_next(Function *, Value *);

#endif /* INCLUDE_GUARD_B55311C7_57F5_41B3_92DD_0759ECC346E7 */
