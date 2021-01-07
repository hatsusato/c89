#include "type.h"

#include "builder.h"
#include "compare.h"
#include "module.h"
#include "pool.h"
#include "type/struct.h"
#include "utility.h"

struct struct_TypePool {
  Pool *pool;
};

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

Type *builder_type(Builder *builder, TypeSpec *spec) {
  Module *module = builder_get_module(builder);
  Type key, *type;
  type_init_spec(&key, spec);
  type = module_find_type(module, &key);
  if (!type) {
    type = type_new();
    type_init_spec(type, spec);
    module_insert_type(module, type);
  }
  return type;
}
Type *builder_type_void(Builder *builder) {
  UTILITY_UNUSED(builder);
  return type_void();
}
Type *builder_type_int(Builder *builder) {
  Module *module = builder_get_module(builder);
  TypeSpec *spec = type_spec_new();
  Type key, *type;
  type_spec_set(spec, TYPE_SPEC_INT);
  type_init_spec(&key, spec);
  type_spec_delete(spec);
  type = module_find_type(module, &key);
  if (!type) {
    type = type_new();
    type_init_spec(type, spec);
    module_insert_type(module, type);
  }
  return type;
}
Type *builder_type_integer(Builder *builder, int size) {
  Module *module = builder_get_module(builder);
  TypePool *pool = module_get_type(module);
  Type *found;
  Type type;
  type_init_integer(&type, size);
  found = module_find_type(module, &type);
  return found ? found : type_pool_new_integer(pool, size);
}
Type *builder_type_pointer(Builder *builder, Type *base) {
  Module *module = builder_get_module(builder);
  TypePool *pool = module_get_type(module);
  Type *found;
  Type type;
  type_init_pointer(&type, base);
  found = module_find_type(module, &type);
  return found ? found : type_pool_new_pointer(pool, base);
}
Type *builder_type_label(Builder *builder) {
  UTILITY_UNUSED(builder);
  return type_label();
}
