#ifndef INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1
#define INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1

#include "builder/types.h"

typedef enum {
  TYPE_SPEC_VOID,
  TYPE_SPEC_CHAR,
  TYPE_SPEC_SHORT,
  TYPE_SPEC_INT,
  TYPE_SPEC_LONG,
  TYPE_SPEC_FLOAT,
  TYPE_SPEC_DOUBLE,
  TYPE_SPEC_SIGNED,
  TYPE_SPEC_UNSIGNED,
  TYPE_SPEC_COUNT
} TypeSpecIndex;

Bool type_is_void(Type *);
void type_print(Type *);
void type_print_elem(Type *);

TypePool *type_pool_new(void);
void type_pool_delete(TypePool *);

Type *builder_type_void(Builder *);
Type *builder_type_integer(Builder *, int);
Type *builder_type_pointer(Builder *, Type *);
Type *builder_type_label(Builder *);

#endif /* INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1 */
