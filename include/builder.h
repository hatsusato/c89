#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "ir/builder_type.h"
#include "ir/register_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Builder *builder_new(void);
void builder_delete(Builder *);
void builder_build(Builder *, Sexp *);
Register *builder_register(Builder *);
Value *builder_value_register(Builder *, Register *);
Value *builder_value_integer_constant(Builder *, Sexp *);
Value *builder_expression(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
