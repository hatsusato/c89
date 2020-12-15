#ifndef INCLUDE_GUARD_864F4242_61F0_4E5F_92C4_5C7E06797758
#define INCLUDE_GUARD_864F4242_61F0_4E5F_92C4_5C7E06797758

#include "ir/stack_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Value *stack_declaration(Stack *, Sexp *);
Value *stack_init_declarator(Stack *, Sexp *);
Value *stack_declarator(Stack *, Sexp *);
Value *stack_direct_declarator(Stack *, Sexp *);

#endif /* INCLUDE_GUARD_864F4242_61F0_4E5F_92C4_5C7E06797758 */
