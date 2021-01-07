#ifndef INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1
#define INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1

#include "builder/types.h"
#include "pool/types.h"
#include "type/print.h"
#include "type/spec.h"

Pool *type_pool_new(void);
void type_pool_delete(Pool *);

Bool type_equals(Type *, Type *);
Bool type_is_void(Type *);
int type_sizeof(Type *);

Type *builder_type(Builder *, TypeSpec *);
Type *builder_type_void(Builder *);
Type *builder_type_bool(Builder *);
Type *builder_type_int(Builder *);
Type *builder_type_pointer(Builder *, Type *);
Type *builder_type_label(Builder *);

#endif /* INCLUDE_GUARD_288C5A5F_4870_4133_85EB_DBA30CC323B1 */
