#ifndef INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1
#define INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1

#include "builder/types.h"
#include "type/spec.h"

Bool type_is_void(Type *);
void type_print(Type *);
void type_print_elem(Type *);

TypeSpec *type_spec_new(void);
void type_spec_delete(TypeSpec *);
void type_spec_set(TypeSpec *, TypeSpecIndex);
void type_spec_reset(TypeSpec *);

TypePool *type_pool_new(void);
void type_pool_delete(TypePool *);

Type *builder_type_void(Builder *);
Type *builder_type_integer(Builder *, int);
Type *builder_type_pointer(Builder *, Type *);
Type *builder_type_label(Builder *);

#endif /* INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1 */
