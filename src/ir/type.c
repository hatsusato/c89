#include "type.h"

#include "compare/compare.h"
#include "ir/type/struct.h"
#include "set/set.h"
#include "utility/utility.h"

static int type_do_cmp(const Type *lhs, const Type *rhs) {
  VectorCmpElem l = lhs, r = rhs;
  return type_cmp_for_vector(&l, &r);
}

int type_cmp_for_vector(const VectorCmpElem *lhs, const VectorCmpElem *rhs) {
  const Type *l = *lhs, *r = *rhs;
  if (l->kind != r->kind) {
    return (l->kind < r->kind) ? -1 : 1;
  }
  switch (l->kind) {
  case TYPE_INTEGER:
    return utility_intcmp(l->data.size, r->data.size);
  case TYPE_POINTER:
    l = l->data.type;
    r = r->data.type;
    return type_do_cmp(l, r);
  default:
    return 0;
  }
}
void type_delete(VectorElem type) {
  UTILITY_FREE(type);
}
Compare *type_compare_new(void) {
  return compare_new_for_vector(type_cmp_for_vector);
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
