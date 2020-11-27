#ifndef INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A
#define INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A

#include "ir/register_type.h"
#include "ir/value_type.h"
#include "sexp_type.h"
#include "vector/vector_type.h"

Vector *value_pool_new(void);
void value_pool_delete(Vector *);
Value *value_register(Register *);
Value *value_integer_constant(Sexp *);

#endif /* INCLUDE_GUARD_FE2AA6D9_B675_4B2E_839A_2B085264192A */
