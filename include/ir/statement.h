#ifndef INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979
#define INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979

#include "ir/builder_type.h"
#include "sexp_type.h"

void builder_statement(Builder *, Sexp *);
void builder_compound_statement(Builder *, Sexp *);
void builder_expression_statement(Builder *, Sexp *);
void builder_jump_statement(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_C7C93740_6608_4112_98EA_4A89E91D8979 */
