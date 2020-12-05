#ifndef INCLUDE_GUARD_B55311C7_57F5_41B3_92DD_0759ECC346E7
#define INCLUDE_GUARD_B55311C7_57F5_41B3_92DD_0759ECC346E7

#include "ir/function_type.h"
#include "ir/pool_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

typedef enum {
  FUNCTION_FUNC,
  FUNCTION_ALLOCS,
  FUNCTION_ENTRY,
  FUNCTION_CURRENT,
  FUNCTION_NEXT,
  FUNCTION_RET,
  FUNCTION_COUNT
} FunctionMember;

Function *function_new(void);
void function_delete(Function *);
Value *function_get(Function *, FunctionMember);
void function_set(Function *, FunctionMember, Value *);
void function_init(Function *, Pool *, Sexp *);
void function_finish(Function *);

#endif /* INCLUDE_GUARD_B55311C7_57F5_41B3_92DD_0759ECC346E7 */
