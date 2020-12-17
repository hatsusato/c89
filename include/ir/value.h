#ifndef INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A
#define INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A

#include "ir/block_type.h"
#include "ir/value_kind.h"
#include "ir/value_type.h"
#include "sexp_type.h"
#include "types.h"

Value *value_new(ValueKind);
void value_delete(Value *);
Value *value_of(void *);
void value_set_value(Value *, const void *);
Value *value_at(Value *, Index);
Size value_length(Value *);
ValueKind value_kind(Value *);
void value_print(Value *);
const char *value_kind_show(Value *);

#endif /* INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A */
