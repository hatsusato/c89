#ifndef INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979
#define INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979

#include "ir/stack_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Value *stack_statement(Stack *, Sexp *);
Value *stack_labeled_statement(Stack *, Sexp *);
Value *stack_compound_statement(Stack *, Sexp *);
Value *stack_expression_statement(Stack *, Sexp *);
Value *stack_selection_statement(Stack *, Sexp *);
Value *stack_iteration_statement(Stack *, Sexp *);
Value *stack_jump_statement(Stack *, Sexp *);

#endif /* INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979 */
