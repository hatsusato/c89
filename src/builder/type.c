#include "type.h"

#include <stdio.h>

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
static Type *type_new(void) {
  Type *type = UTILITY_MALLOC(Type);
  type->size = 0;
  return type;
}
static void type_delete(ElemType type) {
  UTILITY_FREE(type);
}

void type_print(Type *type) {
  printf("i");
  if (type) {
    printf("%d", type->size);
  }
}

TypePool *type_pool_new(void) {
  TypePool *pool = UTILITY_MALLOC(TypePool);
  Compare *compare = compare_new(type_cmp);
  pool->pool = pool_new(type_delete, compare);
  return pool;
}
void type_pool_delete(TypePool *pool) {
  pool_delete(pool->pool);
  UTILITY_FREE(pool);
}
Type *type_pool_integer(TypePool *pool, int size) {
  Type key;
  const ElemType *found;
  key.size = size;
  found = pool_find(pool->pool, &key);
  if (found) {
    return *found;
  } else {
    Type *type = type_new();
    type->size = size;
    pool_insert(pool->pool, type);
    return type;
  }
}
