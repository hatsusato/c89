#ifndef INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1
#define INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1

#include "builder/types.h"

Type *type_void(void);
Type *type_label(void);
void type_print(Type *);
void type_print_elem(Type *);

TypePool *type_pool_new(void);
void type_pool_delete(TypePool *);

Type *builder_type_void(Builder *);
Type *builder_type_integer(Builder *, int);
Type *builder_type_pointer(Builder *, Type *);
Type *builder_type_label(Builder *);

#endif /* INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1 */
