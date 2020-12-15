#ifndef INCLUDE_GUARD_E38EAC74_338A_4A0A_A889_55ABA2B7FBE8
#define INCLUDE_GUARD_E38EAC74_338A_4A0A_A889_55ABA2B7FBE8

#include "ir/stack_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

const char *stack_identifier_symbol(Sexp *);
Value *stack_identifier(Stack *, Sexp *);
Value *stack_integer_constant(Stack *, Sexp *);

#endif /* INCLUDE_GUARD_E38EAC74_338A_4A0A_A889_55ABA2B7FBE8 */
