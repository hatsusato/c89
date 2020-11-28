#ifndef INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A
#define INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A

#include "ir/builder_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"

ValueKind value_kind(Value *);
Value *value_integer_constant(Sexp *);
void value_set_id(Builder *, Value *);

#endif /* INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A */
