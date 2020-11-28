#ifndef INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E
#define INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E

#include "ir/builder_type.h"
#include "ir/register_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Builder *builder_new(void);
void builder_delete(Builder *);
void builder_build(Builder *, Sexp *);
Value *builder_register(Builder *);
Value *builder_expression(Builder *, Sexp *);
int builder_fresh_id(Builder *);
RegisterGenerator *builder_generator(Builder *);
Value *builder_alloc_value(Builder *, ValueKind);

#endif /* INCLUDE_GUARD_563AF498_DA6F_4E09_B103_794E175C655E */
