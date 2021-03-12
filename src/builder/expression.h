#ifndef INCLUDE_GUARD_1A152785_989B_4CD5_84BE_B19C1B797FEB
#define INCLUDE_GUARD_1A152785_989B_4CD5_84BE_B19C1B797FEB

#include "utility/types.h"

void builder_primary_expression(Builder *, Sexp *);
void builder_postfix_expression(Builder *, Sexp *);
void builder_argument_expression_list(Builder *, Sexp *);
void builder_unary_expression(Builder *, Sexp *);
void builder_cast_expression(Builder *, Sexp *);
void builder_multiplicative_expression(Builder *, Sexp *);
void builder_additive_expression(Builder *, Sexp *);
void builder_shift_expression(Builder *, Sexp *);
void builder_relational_expression(Builder *, Sexp *);
void builder_equality_expression(Builder *, Sexp *);
void builder_and_expression(Builder *, Sexp *);
void builder_exclusive_or_expression(Builder *, Sexp *);
void builder_inclusive_or_expression(Builder *, Sexp *);
void builder_logical_and_expression(Builder *, Sexp *);
void builder_logical_or_expression(Builder *, Sexp *);
void builder_conditional_expression(Builder *, Sexp *);
void builder_assignment_expression(Builder *, Sexp *);
void builder_expression(Builder *, Sexp *);
void builder_constant_expression(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_1A152785_989B_4CD5_84BE_B19C1B797FEB */
