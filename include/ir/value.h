#ifndef INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A
#define INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A

#include "ir/register_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"

Value *value_new(ValueKind);
void value_delete(Value *);
ValueKind value_kind(Value *);
void value_init(Value *, ValueKind);
void value_print(Value *);
void value_set_reg(RegisterGenerator *, Value *);

#endif /* INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A */
