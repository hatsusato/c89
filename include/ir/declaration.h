#ifndef INCLUDE_GUARD_864F4242_61F0_4E5F_92C4_5C7E06797758
#define INCLUDE_GUARD_864F4242_61F0_4E5F_92C4_5C7E06797758

#include "builder_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Value *stack_declaration(Builder *, Sexp *);
Value *stack_init_declarator(Builder *, Sexp *);
Value *stack_declarator(Builder *, Sexp *);
Value *stack_direct_declarator(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_864F4242_61F0_4E5F_92C4_5C7E06797758 */
