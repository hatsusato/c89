#include "type.h"

#include "compare.h"
#include "pool.h"
#include "utility.h"

struct struct_Type {
  int size;
};

struct struct_TypePool {
  Pool *pool;
};

static int type_cmp(ElemType lhs, ElemType rhs, CompareExtra extra) {
  Type *l = lhs, *r = rhs;
  UTILITY_UNUSED(extra);
  return (l->size < r->size) ? -1 : (l->size > r->size);
}
static void type_pool_delete_pool(ElemType pool) {
  type_delete(pool);
}

Type *type_new(void) {
  Type *type = UTILITY_MALLOC(Type);
  type->size = 0;
  return type;
}
void type_delete(Type *type) {
  UTILITY_FREE(type);
}

TypePool *type_pool_new(void) {
  TypePool *pool = UTILITY_MALLOC(TypePool);
  Compare *compare = compare_new(type_cmp);
  pool->pool = pool_new(type_pool_delete_pool, compare);
  return pool;
}
void type_pool_delete(TypePool *pool) {
  pool_delete(pool->pool);
  UTILITY_FREE(pool);
}
