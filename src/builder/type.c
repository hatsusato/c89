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
  TYPE_LABEL,
  TYPE_KIND_COUNT
} TypeKind;

struct struct_Type {
  TypeKind kind;
  union {
    int size;
    Type *type;
  } data;
};

struct struct_TypeSpec {
  Bool spec[TYPE_SPEC_COUNT];
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
  case TYPE_INTEGER:
    return utility_intcmp(l->data.size, r->data.size);
  case TYPE_POINTER:
    return type_cmp(l->data.type, r->data.type, extra);
  default:
    return 0;
  }
}
static Type *type_new(void) {
  Type *type = UTILITY_MALLOC(Type);
  type->kind = TYPE_KIND_COUNT;
  type->data.size = 0;
  return type;
}
static void type_delete(ElemType type) {
  UTILITY_FREE(type);
}
static void type_init_integer(Type *type, int size) {
  type->kind = TYPE_INTEGER;
  type->data.size = size;
}
static void type_init_pointer(Type *type, Type *ptr) {
  type->kind = TYPE_POINTER;
  type->data.type = ptr;
}

static Type *type_pool_new_integer(TypePool *pool, int size) {
  Type *type = type_new();
  type_init_integer(type, size);
  pool_insert(pool->pool, type);
  return type;
}
static Type *type_pool_new_pointer(TypePool *pool, Type *ptr) {
  Type *type = type_new();
  type_init_pointer(type, ptr);
  pool_insert(pool->pool, type);
  return type;
}

static Type *type_void(void) {
  static Type type;
  type.kind = TYPE_VOID;
  type.data.size = 0;
  return &type;
}
static Type *type_label(void) {
  static Type type;
  type.kind = TYPE_LABEL;
  type.data.size = 0;
  return &type;
}

Bool type_is_void(Type *type) {
  return TYPE_VOID == type->kind;
}
void type_print(Type *type) {
  switch (type ? type->kind : TYPE_KIND_COUNT) {
  case TYPE_VOID:
    printf("void");
    break;
  case TYPE_INTEGER:
    printf("i%d", type->data.size);
    break;
  case TYPE_POINTER:
    type_print(type->data.type);
    printf("*");
    break;
  case TYPE_LABEL:
    printf("label");
    break;
  default:
    printf("null");
    break;
  }
}
void type_print_elem(Type *type) {
  if (TYPE_POINTER == type->kind) {
    type_print(type->data.type);
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
  UTILITY_UNUSED(builder);
  return type_void();
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
Type *builder_type_pointer(Builder *builder, Type *base) {
  Module *module = builder_get_module(builder);
  TypePool *pool = module_get_type(module);
  const ElemType *found;
  Type type;
  type_init_pointer(&type, base);
  found = pool_find(pool->pool, &type);
  return found ? *found : type_pool_new_pointer(pool, base);
}
Type *builder_type_label(Builder *builder) {
  UTILITY_UNUSED(builder);
  return type_label();
}
