#ifndef INCLUDE_GUARD_864F4242_61F0_4E5F_92C4_5C7E06797758
#define INCLUDE_GUARD_864F4242_61F0_4E5F_92C4_5C7E06797758

#include "builder/types.h"

void builder_declaration(Builder *, Sexp *);
void builder_declaration_specifiers(Builder *, Sexp *);
void builder_init_declarator_list(Builder *, Sexp *);
void builder_init_declarator(Builder *, Sexp *);
void builder_storage_class_specifier(Builder *, Sexp *);
void builder_type_specifier(Builder *, Sexp *);
void builder_struct_or_union_specifier(Builder *, Sexp *);
void builder_struct_declaration_list(Builder *, Sexp *);
void builder_struct_declaration(Builder *, Sexp *);
void builder_specifier_qualifier_list(Builder *, Sexp *);
void builder_struct_declarator_list(Builder *, Sexp *);
void builder_struct_declarator(Builder *, Sexp *);
void builder_enum_specifier(Builder *, Sexp *);
void builder_enumerator_list(Builder *, Sexp *);
void builder_enumerator(Builder *, Sexp *);
void builder_type_qualifier(Builder *, Sexp *);
void builder_declarator(Builder *, Sexp *);
void builder_direct_declarator(Builder *, Sexp *);
void builder_pointer(Builder *, Sexp *);
void builder_type_qualifier_list(Builder *, Sexp *);
void builder_parameter_list(Builder *, Sexp *);
void builder_parameter_declaration(Builder *, Sexp *);
void builder_identifier_list(Builder *, Sexp *);
void builder_type_name(Builder *, Sexp *);
void builder_abstract_declarator(Builder *, Sexp *);
void builder_direct_abstract_declarator(Builder *, Sexp *);
void builder_typedef_name(Builder *, Sexp *);
void builder_initializer(Builder *, Sexp *);
void builder_initializer_list(Builder *, Sexp *);

#endif /* INCLUDE_GUARD_864F4242_61F0_4E5F_92C4_5C7E06797758 */
