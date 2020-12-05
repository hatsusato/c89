#ifndef INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A
#define INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A

#include "ir/register_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"
#include "types.h"

Value *value_new(ValueKind);
void value_delete(Value *);
void value_insert(Value *, Value *);
void value_pop(Value *);
void value_append(Value *, const Value *);
void value_set_value(Value *, const void *);
Value *value_at(Value *, Index);
Size value_length(Value *);
Value *value_last(Value *);
ValueKind value_kind(Value *);
void value_print(Value *);
void value_pretty(Value *);
void value_set_reg(RegisterGenerator *, Value *);
const char *value_kind_show(Value *);
Bool value_is_instruction(Value *);
Bool value_is_terminator(Value *);

#endif /* INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A */
