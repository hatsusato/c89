#ifndef INCLUDE_GUARD_E38EAC74_338A_4A0A_A889_55ABA2B7FBE8
#define INCLUDE_GUARD_E38EAC74_338A_4A0A_A889_55ABA2B7FBE8

#include "utility/types.h"

void builder_identifier(Builder *, Sexp *);
void builder_typedef_identifier(Builder *, Sexp *);
void builder_floating_constant(Builder *, Sexp *);
void builder_integer_constant(Builder *, Sexp *);
void builder_enumeration_constant(Builder *, Sexp *);
void builder_character_constant(Builder *, Sexp *);
void builder_string_literal(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_E38EAC74_338A_4A0A_A889_55ABA2B7FBE8 */
