#ifndef INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979
#define INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979

#include "ir/stack_type.h"
#include "sexp_type.h"

void stack_statement(Stack *, Sexp *);
void stack_compound_statement(Stack *, Sexp *);
void stack_expression_statement(Stack *, Sexp *);
void stack_selection_statement(Stack *, Sexp *);
void stack_jump_statement(Stack *, Sexp *);

#endif /* INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979 */
