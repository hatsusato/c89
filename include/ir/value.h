#ifndef INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A
#define INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A

#include "ir/value_type.h"
#include "set/set_type.h"
#include "sexp_type.h"

Set *value_pool_new(void);
void value_pool_delete(Set *);
Value *value_register(void);
Value *value_integer_constant(Sexp *);
void value_delete(Value *);

#endif /* INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A */
