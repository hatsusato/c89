#ifndef INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979
#define INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979

#include "builder_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Value *stack_statement(Builder *, Sexp *);
Value *stack_labeled_statement(Builder *, Sexp *);
Value *stack_compound_statement(Builder *, Sexp *);
Value *stack_expression_statement(Builder *, Sexp *);
Value *stack_selection_statement(Builder *, Sexp *);
Value *stack_iteration_statement(Builder *, Sexp *);
Value *stack_jump_statement(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979 */
