#include "type.h"

#include <stdio.h>

#include "builder.h"
#include "compare.h"
#include "pool.h"
#include "utility.h"

typedef enum {
  TYPE_VOID,
  TYPE_INTEGER,
  TYPE_POINTER,
  TYPE_KIND_COUND
} TypeKind;

struct struct_Type {
  TypeKind kind;
  union {
    int size;
    Type *type;
  } data;
};

struct struct_TypePool {
  Pool *pool;
};

static int type_cmp(ElemType lhs, ElemType rhs, CompareExtra extra) {
  Type *l = lhs, *r = rhs;
  if (l->kind != r->kind) {
    return (l->kind < r->kind) ? -1 : 1;
  }
  switch (l->kind) {
  case TYPE_VOID:
    return 0;
  case TYPE_INTEGER:
    return utility_intcmp(l->data.size, r->data.size);
  case TYPE_POINTER:
    return type_cmp(l->data.type, r->data.type, extra);
  default:
    UTILITY_ASSERT(0);
    return 0;
  }
}
static Type *type_new(void) {
  Type *type = UTILITY_MALLOC(Type);
  type->kind = TYPE_KIND_COUND;
  type->data.size = 0;
  return type;
}
static void type_delete(ElemType type) {
  UTILITY_FREE(type);
}
static void type_init_void(Type *type) {
  type->kind = TYPE_VOID;
  type->data.size = 0;
}
static void type_init_integer(Type *type, int size) {
  type->kind = TYPE_INTEGER;
  type->data.size = size;
}

static Type *type_pool_new_void(TypePool *pool) {
  Type *type = type_new();
  type_init_void(type);
  pool_insert(pool->pool, type);
  return type;
}
static Type *type_pool_new_integer(TypePool *pool, int size) {
  Type *type = type_new();
  type_init_integer(type, size);
  pool_insert(pool->pool, type);
  return type;
}

void type_print(Type *type) {
  printf("i");
  if (type) {
    printf("%d", type->data.size);
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

Type *builder_type_void(Builder *builder) {
  Module *module = builder_get_module(builder);
  TypePool *pool = module_get_type(module);
  const ElemType *found;
  Type type;
  type_init_void(&type);
  found = pool_find(pool->pool, &type);
  return found ? *found : type_pool_new_void(pool);
}
Type *builder_type_integer(Builder *builder, int size) {
  Module *module = builder_get_module(builder);
  TypePool *pool = module_get_type(module);
  const ElemType *found;
  Type type;
  type_init_integer(&type, size);
  found = pool_find(pool->pool, &type);
  return found ? *found : type_pool_new_integer(pool, size);
}
