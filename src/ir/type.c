#include "type.h"

#include "ir/type/struct.h"
#include "set/set.h"
#include "utility/utility.h"

static int type_do_cmp(const Type *, const Type *);
static void type_delete(Generic type) {
  UTILITY_FREE(type);
}
static int type_cmp(const ConstGeneric *lhs, const ConstGeneric *rhs) {
  const Type *l = *lhs, *r = *rhs;
  if (l->kind != r->kind) {
    return (l->kind < r->kind) ? -1 : 1;
  }
  switch (l->kind) {
  case TYPE_INTEGER:
    return utility_intcmp(l->data.size, r->data.size);
  case TYPE_POINTER:
    return type_do_cmp(l->data.type, r->data.type);
  default:
    return 0;
  }
}
static int type_do_cmp(const Type *lhs, const Type *rhs) {
  ConstGeneric l = lhs, r = rhs;
  return type_cmp(&l, &r);
}

Bool type_equals(Type *lhs, Type *rhs) {
  return 0 == type_do_cmp(lhs, rhs);
}
Bool type_is_void(Type *type) {
  return TYPE_INTEGER == type->kind && 0 == type->data.size;
}
int type_sizeof(Type *type) {
  return TYPE_INTEGER == type->kind ? type->data.size : 0;
}

TypePool *type_pool_new(void) {
  return set_new(type_delete, type_cmp);
}
void type_pool_delete(TypePool *pool) {
  set_delete(pool);
}
void type_pool_insert(TypePool *pool, Type *type) {
  set_insert(pool, type);
}
Type *type_pool_find(TypePool *pool, Type *type) {
  return (Type *)set_find(pool, type);
}
