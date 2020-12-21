#ifndef INCLUDE_GUARD_1A152785_989B_4CD5_84BE_B19C1B797FEB
#define INCLUDE_GUARD_1A152785_989B_4CD5_84BE_B19C1B797FEB

#include "builder_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Value *stack_additive_expression(Builder *, Sexp *);
Value *stack_assignment_expression(Builder *, Sexp *);
Value *stack_constant_expression(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_1A152785_989B_4CD5_84BE_B19C1B797FEB */
