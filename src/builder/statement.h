#ifndef INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979
#define INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979

#include "builder/type.h"
#include "sexp_type.h"
#include "value/type.h"

Value *builder_statement(Builder *, Sexp *);
Value *builder_labeled_statement(Builder *, Sexp *);
Value *builder_compound_statement(Builder *, Sexp *);
Value *builder_expression_statement(Builder *, Sexp *);
Value *builder_selection_statement(Builder *, Sexp *);
Value *builder_iteration_statement(Builder *, Sexp *);
Value *builder_jump_statement(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979 */
