#include "type.h"

#include <stdio.h>

#include "builder.h"
#include "compare.h"
#include "pool.h"
#include "type/struct.h"
#include "utility.h"

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
  type->kind = TYPE_INTEGER;
  type->data.size = 0;
  return type;
}
static void type_delete(ElemType type) {
  UTILITY_FREE(type);
}
static void type_init_spec(Type *type, TypeSpec *spec) {
  if (type_spec_get(spec, TYPE_SPEC_FLOAT)) {
    UTILITY_ASSERT(0);
  } else if (type_spec_get(spec, TYPE_SPEC_DOUBLE)) {
    UTILITY_ASSERT(0);
  } else {
    type->kind = TYPE_INTEGER;
    if (type_spec_get(spec, TYPE_SPEC_VOID)) {
      type->data.size = 0;
    } else if (type_spec_get(spec, TYPE_SPEC_CHAR)) {
      type->data.size = 8;
    } else if (type_spec_get(spec, TYPE_SPEC_SHORT)) {
      type->data.size = 16;
    } else if (type_spec_get(spec, TYPE_SPEC_LONG)) {
      type->data.size = 64;
    } else {
      type->data.size = 32;
    }
  }
}
static Type type_tmp_integer(int size) {
  Type type;
  type.kind = TYPE_INTEGER;
  type.data.size = size;
  return type;
}
static void type_init_integer(Type *type, int size) {
  type->kind = TYPE_INTEGER;
  type->data.size = size;
}
static void type_pool_insert_integer(Pool *pool, int size) {
  Type *type = type_new();
  type_init_integer(type, size);
  UTILITY_ASSERT(!pool_find(pool, type));
  pool_insert(pool, type);
}

Pool *type_pool_new(void) {
  Compare *type_compare = compare_new(type_cmp);
  Pool *pool = pool_new(type_delete, type_compare);
  type_pool_insert_integer(pool, 0);
  return pool;
}
void type_pool_delete(Pool *pool) {
  pool_delete(pool);
}

Bool type_is_void(Type *type) {
  return TYPE_INTEGER == type->kind && 0 == type->data.size;
}
void type_print(Type *type) {
  switch (type ? type->kind : TYPE_KIND_COUNT) {
  case TYPE_INTEGER:
    if (0 == type->data.size) {
      printf("void");
    } else {
      printf("i%d", type->data.size);
    }
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

static Type *builder_new_type(Builder *builder, Type *type) {
  Module *module = builder_get_module(builder);
  Type *found = module_find_type(module, type);
  if (!found) {
    found = type_new();
    *found = *type;
    module_insert_type(module, found);
  }
  return found;
}

Type *builder_type(Builder *builder, TypeSpec *spec) {
  Type type;
  type_init_spec(&type, spec);
  return builder_new_type(builder, &type);
}
Type *builder_type_void(Builder *builder) {
  Type tmp = type_tmp_integer(0);
  return builder_new_type(builder, &tmp);
}
Type *builder_type_bool(Builder *builder) {
  Type tmp = type_tmp_integer(1);
  return builder_new_type(builder, &tmp);
}
Type *builder_type_int(Builder *builder) {
  Type tmp = type_tmp_integer(32);
  return builder_new_type(builder, &tmp);
}
Type *builder_type_pointer(Builder *builder, Type *base) {
  Type tmp;
  tmp.kind = TYPE_POINTER;
  tmp.data.type = base;
  return builder_new_type(builder, &tmp);
}
Type *builder_type_label(Builder *builder) {
  Type tmp;
  tmp.kind = TYPE_LABEL;
  tmp.data.size = 0;
  return builder_new_type(builder, &tmp);
}
