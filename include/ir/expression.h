#ifndef INCLUDE_GUARD_1A152785_989B_4CD5_84BE_B19C1B797FEB
#define INCLUDE_GUARD_1A152785_989B_4CD5_84BE_B19C1B797FEB

#include "ir/stack_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Value *stack_additive_expression(Stack *, Sexp *);
Value *stack_assignment_expression(Stack *, Sexp *);
Value *stack_constant_expression(Stack *, Sexp *);

#endif /* INCLUDE_GUARD_1A152785_989B_4CD5_84BE_B19C1B797FEB */
