#ifndef INCLUDE_GUARD_E38EAC74_338A_4A0A_A889_55ABA2B7FBE8
#define INCLUDE_GUARD_E38EAC74_338A_4A0A_A889_55ABA2B7FBE8

#include "builder/type.h"
#include "builder/value/type.h"
#include "sexp_type.h"

const char *builder_identifier_symbol(Sexp *);
Value *builder_identifier(Builder *, Sexp *);
Value *builder_integer_constant(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_E38EAC74_338A_4A0A_A889_55ABA2B7FBE8 */
