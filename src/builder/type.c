#include "type.h"

#include "builder.h"
#include "type/struct.h"
#include "utility.h"

static void type_init_integer(Type *type, int size) {
  type->kind = TYPE_INTEGER;
  type->data.size = size;
}
static void type_init_pointer(Type *type, Type *ptr) {
  type->kind = TYPE_POINTER;
  type->data.type = ptr;
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
Type *builder_type_bool(Builder *builder) {
  Module *module = builder_get_module(builder);
  Type key, *type;
  key.kind = TYPE_INTEGER;
  key.data.size = 1;
  type = module_find_type(module, &key);
  if (!type) {
    type = type_new();
    type_init_integer(type, 1);
    module_insert_type(module, type);
  }
  return type;
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
Type *builder_type_pointer(Builder *builder, Type *base) {
  Module *module = builder_get_module(builder);
  Type key, *type;
  type_init_pointer(&key, base);
  type = module_find_type(module, &key);
  if (!type) {
    type = type_new();
    type_init_pointer(type, base);
    module_insert_type(module, type);
  }
  return type;
}
Type *builder_type_label(Builder *builder) {
  UTILITY_UNUSED(builder);
  return type_label();
}
